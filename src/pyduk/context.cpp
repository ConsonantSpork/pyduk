#include "context.hpp"
#include "exceptions.hpp"
#include <string>
#include <sstream>

namespace bpy = boost::python;

namespace pyduk {
    Context::Context() {
        ctx = duk_create_heap_default();
    }

    Context::~Context() {
        duk_destroy_heap(ctx);
    }

    bpy::object Context::run(std::string source) {
        if(duk_peval_string(ctx, source.c_str()))
            throw RuntimeException("Runtime error");
        return idx_to_bpyobj(-1);
    }

    bpy::object Context::idx_to_bpyobj(duk_size_t idx) {
        switch(duk_get_type(ctx, idx)) {
            case DUK_TYPE_UNDEFINED: case DUK_TYPE_NULL:
                return bpy::object();
            case DUK_TYPE_BOOLEAN:
                return bpy::object((bool) duk_get_boolean(ctx, idx));
            case DUK_TYPE_NUMBER:
                return number_idx_to_bpyobj(idx);
            case DUK_TYPE_STRING:
                return bpy::object(std::string(duk_get_string(ctx, idx)));
            case DUK_TYPE_OBJECT:  // This case for arrays too
                return object_idx_to_bpyobj(idx);
            case DUK_TYPE_BUFFER:
                return buffer_idx_to_bpyobj(idx);
            case DUK_TYPE_POINTER:
            case DUK_TYPE_LIGHTFUNC:
            default:
                throw ConversionException("Unable to convert value");
        }
    }

    bpy::object Context::number_idx_to_bpyobj(duk_size_t idx) {
        double num = duk_get_number(ctx, idx);
        if (round(num) == num)
            return bpy::object((int32_t) num);
        return bpy::object(num);
    }

    bool isFloat(std::string myString) {
        std::istringstream iss(myString);
        float f;
        iss >> std::noskipws >> f;
        return iss.eof() && !iss.fail();
    }

    bool Context::object_is_array(duk_size_t idx) {
        duk_get_prop_string(ctx, idx, "length");
        bool is_array = !duk_is_undefined(ctx, -1);
        duk_pop(ctx);
        return is_array;
    }

    bpy::object Context::object_idx_to_bpyobj(duk_size_t idx) {
        if (object_is_array(idx))
            return array_idx_to_bpyobj(idx);

        bpy::dict ret;
        duk_enum(ctx, idx, 0);
        while(duk_next(ctx, -1, 1 /* get key and value */)) {
            ret[idx_to_bpyobj(-2)] = idx_to_bpyobj(-1);
            duk_pop_2(ctx);  // remove key and value from stack
        }
        duk_pop(ctx); // pop enum
        return ret;
    }

    bpy::object Context::array_idx_to_bpyobj(duk_size_t idx) {
        bpy::list ret;
        duk_size_t n = duk_get_length(ctx, idx);
        for (duk_size_t i = 0; i < n; i++) {
            duk_get_prop_index(ctx, idx, i);
            ret.append(idx_to_bpyobj(-1));
            duk_pop(ctx);
        }
        return ret;
    }

    bpy::object Context::buffer_idx_to_bpyobj(duk_size_t idx) {
        return array_idx_to_bpyobj(idx);
    }
}

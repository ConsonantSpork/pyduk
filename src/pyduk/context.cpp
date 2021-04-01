#include "context.hpp"
#include "exceptions.hpp"

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
                return bpy::object((float) duk_get_number(ctx, idx));
            case DUK_TYPE_STRING:
                return bpy::object(std::string(duk_get_string(ctx, idx)));
            case DUK_TYPE_OBJECT:
                return object_idx_to_bpyobj(idx);
            case DUK_TYPE_BUFFER:
                return buffer_idx_to_bpyobj(idx);
            case DUK_TYPE_POINTER:
            case DUK_TYPE_LIGHTFUNC:
            default:
                throw ConversionException("Unable to convert value");
        }
    }

    bpy::object Context::object_idx_to_bpyobj(duk_size_t idx) {
        bpy::dict ret;
        duk_enum(ctx, idx, 0);
        while(duk_next(ctx, -1, 1 /* get key and value */)) {
            ret[idx_to_bpyobj(-2)] = idx_to_bpyobj(-1);
            duk_pop_2(ctx);  // remove key and value from stack
        }
        duk_pop(ctx); // pop enum
        return ret;
    }

    bpy::object Context::buffer_idx_to_bpyobj(duk_size_t idx) {
        throw ConversionException("Unable to convert value");
    }
}

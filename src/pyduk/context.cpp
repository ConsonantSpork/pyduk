#include <iostream>
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
        if(duk_peval_string(ctx, source.c_str())) {
            throw RuntimeException("Runtime error: " + std::string(duk_safe_to_string(ctx, -1)));
            duk_pop(ctx);
        }
        return idx_to_bpyobj(-1);
    }

    bpy::object Context::idx_to_bpyobj(duk_size_t idx) {
        idx = duk_normalize_index(ctx, idx);

        switch(duk_get_type(ctx, idx)) {
            case DUK_TYPE_UNDEFINED: case DUK_TYPE_NULL:
                return bpy::object();
            case DUK_TYPE_BOOLEAN:
                return bpy::object((bool) duk_get_boolean(ctx, idx));
            case DUK_TYPE_NUMBER:
                return number_idx_to_bpyobj(idx);
            case DUK_TYPE_STRING:
                return bpy::object(std::string(duk_get_string(ctx, idx)));
            case DUK_TYPE_OBJECT:
                if (duk_is_array(ctx, idx))
                    return array_idx_to_bpyobj(idx);
                if (idx_obj_instanceof("Boolean", idx))
                    return boolean_obj_idx_to_bpyobj(idx);
                if (idx_obj_instanceof("Number", idx))
                    return number_obj_idx_to_bpyobj(idx);
                if (idx_obj_instanceof("Uint8Array", idx))
                    return uint8_array_to_bpyobj(idx);
                if (idx_obj_instanceof("Int8Array", idx)
                    || idx_obj_instanceof("Uint16Array", idx)
                    || idx_obj_instanceof("Int16Array", idx)
                    || idx_obj_instanceof("Uint32Array", idx)
                    || idx_obj_instanceof("Int32Array", idx)
                    || idx_obj_instanceof("Float32Array", idx)
                    || idx_obj_instanceof("Float64Array", idx))
                {
                    typed_array_to_uint8_array(idx);
                    return uint8_array_to_bpyobj(idx);
                }
                if (idx_obj_instanceof("ArrayBuffer", idx)) {
                    array_buffer_to_uint8_array(idx);
                    return uint8_array_to_bpyobj(idx);
                }
                return object_idx_to_bpyobj(idx);
            case DUK_TYPE_BUFFER:
                return buffer_idx_to_bpyobj(idx);
            case DUK_TYPE_POINTER:
            case DUK_TYPE_LIGHTFUNC:
            default:
                throw ConversionException("Unable to convert value");
        }
    }

    bpy::object Context::boolean_obj_idx_to_bpyobj(duk_size_t idx) {
        std::string res = duk_to_string(ctx, idx);
        return bpy::object(res == "true");
    }

    bpy::object round_double(double num) {
        if (round(num) == num)
            return bpy::object((int32_t) num);
        return bpy::object(num);
    }

    bpy::object Context::number_obj_idx_to_bpyobj(duk_size_t idx) {
        return round_double(duk_to_number(ctx, idx));
    }

    bool Context::idx_obj_instanceof(const std::string test_type, duk_size_t idx) {
        if (duk_peval_string(ctx, test_type.c_str()))
            return false;
        bool res = duk_instanceof(ctx, idx, -1);
        duk_pop(ctx);
        return res;
    }

    bpy::object Context::number_idx_to_bpyobj(duk_size_t idx) {
        return round_double(duk_get_number(ctx, idx));
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
        throw ConversionException("Buffer conversion not implemented");
    }

    // helper function for ArrayBuffer/TypedArray conversions
    void Context::call_single_arg_constructor(duk_size_t result_destination) {
        // Call constructor, result value gets put on top
        duk_new(ctx, 1);
        // Put result in required location and whatever is there already to top
        duk_swap(ctx, result_destination, -1);
        // Pop what was in required location
        duk_pop(ctx);
    }

    void Context::array_buffer_to_uint8_array(duk_size_t idx) {
        duk_eval_string(ctx, "Uint8Array");
        duk_dup(ctx, idx);
        call_single_arg_constructor(idx);
    }

    void Context::typed_array_to_uint8_array(duk_size_t idx) {
        duk_eval_string(ctx, "Uint8Array");
        if(!duk_get_prop_string(ctx, idx, "buffer"))
            throw ConversionException("Could not convert TypedArray: property 'buffer' not found.");
        call_single_arg_constructor(idx);
    }

    duk_size_t Context::get_array_length(duk_size_t idx) {
        duk_get_prop_string(ctx, idx, "length");
        duk_size_t ret = duk_get_uint(ctx, -1);
        duk_pop(ctx);
        return ret;
    }

    bpy::object Context::uint8_array_to_bpyobj(duk_size_t idx) {
        duk_size_t arr_length = get_array_length(idx);
        duk_enum(ctx, idx, DUK_ENUM_ARRAY_INDICES_ONLY);
        char* bytes = new char[arr_length];
        for (int i = 0; duk_next(ctx, -1, 1 /* get key and value */); i++) {
            uint8_t byte_uint = duk_get_uint(ctx, -1);
            bytes[i] = static_cast<char>(byte_uint);
            duk_pop_2(ctx);
        }
        duk_pop(ctx);
        return bpy::object(bpy::handle<>(PyByteArray_FromStringAndSize(bytes, arr_length)));
    }
}

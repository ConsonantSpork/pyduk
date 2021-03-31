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
        duk_eval_string(ctx, source.c_str());
        return top_to_bpyobj();
    }

    bpy::object Context::top_to_bpyobj() {
        switch(duk_get_type(ctx, -1)) {
            case DUK_TYPE_UNDEFINED: case DUK_TYPE_NULL:
                return bpy::object();
            case DUK_TYPE_BOOLEAN:
                return bpy::object((bool) duk_get_boolean(ctx, -1));
            case DUK_TYPE_NUMBER:
                return bpy::object((float) duk_get_number(ctx, -1));
            case DUK_TYPE_STRING:
                return bpy::object(std::string(duk_get_string(ctx, -1)));
            case DUK_TYPE_OBJECT:
                return top_object_to_bpyobj();
            case DUK_TYPE_BUFFER:
                return top_buffer_to_bpyobj();
            case DUK_TYPE_POINTER:
            case DUK_TYPE_LIGHTFUNC:
            default:
                throw new ConversionException("Unable to convert value");
        }
    }

    bpy::object Context::top_object_to_bpyobj() {
        throw new ConversionException("Unable to convert value");
    }

    bpy::object Context::top_buffer_to_bpyobj() {
        throw new ConversionException("Unable to convert value");
    }
}

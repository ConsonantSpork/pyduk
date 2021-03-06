#pragma once

#include <duktape.h>
#include <string>
#include <pyduk.hpp>
#include <boost/python.hpp>
#include "circular_reference_tracker.hpp"

namespace bpy = boost::python;

namespace pyduk {
    /** @brief Main duktape wrapper class to run JavaScript.
     *
     * Allows to run JavaScript code and return Python types.
     *
     * @warning Should not be used in a multi-threaded environment. */
    class Context {
        public:
            static const int USE_GLOBAL_POLYFILL;

            explicit Context(int flags);
            Context(const Context&) = delete;
            Context(const Context&&) = delete;
            ~Context();

            Context& operator=(const Context&) = delete;
            Context& operator=(const Context&&) = delete;

            /** @brief Run source string and return result of last expression.
             *
             *  @param source - source string to run
             *
             *  @returns result converted to Python object */
            bpy::object run(const std::string& source);

        private:
            duk_context* ctx;
            CircularReferenceTracker<bpy::object, uintptr_t> crt;

            bpy::object idx_to_bpyobj_wrapper(duk_idx_t idx);
            bpy::object idx_to_bpyobj(duk_idx_t idx);
            bpy::object number_idx_to_bpyobj(duk_idx_t idx);
            bpy::object object_idx_to_bpyobj(duk_idx_t idx);
            bpy::object array_idx_to_bpyobj(duk_idx_t idx);
            bpy::object buffer_idx_to_bpyobj(duk_idx_t idx);
            bpy::object boolean_obj_idx_to_bpyobj(duk_idx_t idx);
            bpy::object number_obj_idx_to_bpyobj(duk_idx_t idx);
            bpy::object uint8_array_to_bpyobj(duk_idx_t idx);

            uintptr_t get_unique_repr(duk_idx_t idx);
            void call_single_arg_constructor(duk_idx_t result_destination);
            void array_buffer_to_uint8_array(duk_idx_t idx);
            void typed_array_to_uint8_array(duk_idx_t idx);
            duk_size_t get_array_length(duk_idx_t idx);
            bool idx_obj_instanceof(const std::string& test_type, duk_idx_t idx);
    };
}

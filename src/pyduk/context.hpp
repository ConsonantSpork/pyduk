#include <duktape.h>
#include <string>
#include <pyduk.hpp>
#include <boost/python.hpp>

namespace bpy = boost::python;

namespace pyduk {
    /** @brief Main duktape wrapper class to run JavaScript.
     *
     * Allows to run JavaScript code and return Python types.
     *
     * @warning Should not be used in a multi-threaded environment. */
    class Context {
        public:
            Context();
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
            bpy::object run(std::string source);

        private:
            duk_context* ctx;

            bpy::object top_to_bpyobj();
            bpy::object top_object_to_bpyobj();
            bpy::object top_buffer_to_bpyobj();
    };
}

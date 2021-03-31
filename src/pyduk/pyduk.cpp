#include <pyduk.hpp>
#include <boost/python.hpp>
#include "exceptions.hpp"
#include "context.hpp"

namespace bpy = boost::python;

PyObject* duk_exception_base_type = nullptr;
PyObject* duk_conversion_error_type = nullptr;
PyObject* duk_runtime_exception_type = nullptr;

void translate_duk_exception(const pyduk::DukException& exc, PyObject* exc_type) {
  PyObject* args = Py_BuildValue("s", exc.what());
  PyObject* duk_exception_instance = PyObject_Call(exc_type, args, NULL);
  Py_INCREF(duk_exception_instance);

  PyObject* message = PyUnicode_FromString(exc.what());
  PyObject_SetAttrString(duk_exception_instance, "message", message);

  PyErr_SetObject(exc_type, duk_exception_instance);
}

void translate_duk_conversion_exception(const pyduk::ConversionException& exc) {
  translate_duk_exception(exc, duk_conversion_error_type);
}

void translate_duk_runtime_exception(const pyduk::RuntimeException& exc) {
  translate_duk_exception(exc, duk_runtime_exception_type);
}


BOOST_PYTHON_MODULE(PYTHON_MODULE_NAME) {
  bpy::class_<pyduk::Context, boost::noncopyable>("Context")
    .def("run", &pyduk::Context::run);

  duk_conversion_error_type = PyErr_NewException(PYTHON_MODULE_NAME_STRING ".ConversionError", PyExc_RuntimeError, NULL);
  duk_runtime_exception_type = PyErr_NewException(PYTHON_MODULE_NAME_STRING ".JSRuntimeError", PyExc_Exception, NULL);
  bpy::scope().attr("ConversionError") = bpy::handle<>(duk_conversion_error_type);
  bpy::scope().attr("JSRuntimeError") = bpy::handle<>(duk_runtime_exception_type);
  bpy::register_exception_translator<pyduk::ConversionException>(translate_duk_conversion_exception);
  bpy::register_exception_translator<pyduk::RuntimeException>(translate_duk_runtime_exception);
}

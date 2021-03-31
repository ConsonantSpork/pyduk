#include <pyduk.hpp>
#include <boost/python.hpp>
#include "exceptions.hpp"
#include "context.hpp"

namespace bpy = boost::python;

PyObject* duk_conversion_exception_type = nullptr;

void translate_duk_conversion_exception(const pyduk::ConversionException& exc){
  PyObject* args = Py_BuildValue("s", exc.what());
  PyObject* duk_exception_instance = PyObject_Call(duk_conversion_exception_type, args, NULL);
  Py_INCREF(duk_exception_instance);

  PyObject* message = PyUnicode_FromString(exc.what());
  PyObject_SetAttrString(duk_exception_instance, "message", message);

  PyErr_SetObject(duk_conversion_exception_type, duk_exception_instance);
}

BOOST_PYTHON_MODULE(PYTHON_MODULE_NAME) {
  bpy::class_<pyduk::Context, boost::noncopyable>("Context")
    .def("run", &pyduk::Context::run);

  duk_conversion_exception_type = PyErr_NewException(PYTHON_MODULE_NAME_STRING ".ConversionError", PyExc_Exception, NULL);
  bpy::scope().attr("ConversionError") = bpy::handle<>(duk_conversion_exception_type);

  bpy::register_exception_translator<pyduk::ConversionException>(&translate_duk_conversion_exception);
}

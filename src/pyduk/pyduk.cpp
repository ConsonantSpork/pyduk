#include <iostream>
#include <pyduk.hpp>
#include <boost/python.hpp>

namespace bpy = boost::python;

void test() {
    std::cout << PYTHON_MODULE_NAME_STRING
              << " of version "
              << PYTHON_MODULE_VERSION_MAJOR
              << "."
              << PYTHON_MODULE_VERSION_MINOR
              << std::endl;
}

BOOST_PYTHON_MODULE(PYTHON_MODULE_NAME) {
    bpy::def("test", test);
}

#include <gtest/gtest.h>
#include "context_fixture.hpp"
#include <boost/python.hpp>

TEST_F(PyDukContext, string_conversion) {
    EXPECT_EQ(context.run("'Hello, World!'"),
              boost::python::object("Hello, World!"));
}

TEST_F(PyDukContext, integer_conversion) {
    EXPECT_EQ(context.run("1 + 2"),
              boost::python::object("3"));
}

TEST_F(PyDukContext, number_conversion) {
    EXPECT_EQ(context.run("1.2 + 2.3"),
              boost::python::object("3.5"));
}

TEST_F(PyDukContext, boolean_conversion) {
    EXPECT_EQ(context.run("true"),
              boost::python::object(true));
}

TEST_F(PyDukContext, boolean_object_conversion) {
    EXPECT_EQ(context.run("new Boolean(1)"),
              boost::python::object(true));
}

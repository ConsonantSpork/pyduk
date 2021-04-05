#include <gtest/gtest.h>
#include "context_fixture.hpp"
#include <boost/python.hpp>

TEST_F(PyDukContext, string_conversion) {
    EXPECT_EQ(context.run("'Hello, World!'"),
              boost::python::object("Hello, World!"));
}

TEST_F(PyDukContext, integer_conversion) {
    auto actual = context.run("1 + 2");
    EXPECT_EQ(PyLong_Check(actual.ptr()),
              true);
    EXPECT_EQ(actual,
              boost::python::object(3));
}

TEST_F(PyDukContext, number_conversion) {
    EXPECT_EQ(context.run("1.2 + 2.3"),
              boost::python::object(3.5));
}

TEST_F(PyDukContext, boolean_conversion) {
    EXPECT_EQ(context.run("true"),
              boost::python::object(true));
}

TEST_F(PyDukContext, boolean_object_conversion) {
    EXPECT_EQ(context.run("new Boolean(1)"),
              boost::python::object(true));
}

TEST_F(PyDukContext, empty_object_conversion) {
    boost::python::dict expected;
    EXPECT_EQ(context.run("var d = {}; d;"),
              expected);
}

TEST_F(PyDukContext, empty_list_conversion) {
    boost::python::list expected;
    EXPECT_EQ(context.run("var d = []; d;"),
              expected);
}

TEST_F(PyDukContext, list_conversion) {
    boost::python::list expected;
    boost::python::list inner;
    inner.append("inner");
    inner.append("list");
    expected.append(1);
    expected.append(2.0);
    expected.append("hello");
    expected.append(inner);
    EXPECT_EQ(context.run("var d = [1, 2.0, 'hello', ['inner', 'list']]; d;"),
              expected);
}

TEST_F(PyDukContext, number_object) {
    EXPECT_EQ(context.run("new Number(12.0)"),
              boost::python::object(12));
}

TEST_F(PyDukContext, number_object_float) {
    EXPECT_EQ(context.run("new Number(12.4)"),
              boost::python::object(12.4));
}

TEST_F(PyDukContext, buffer_conversion) {
    boost::python::list expected;
    expected.append(1);
    expected.append(2);
    expected.append(3);
    EXPECT_EQ(context.run("new Uint8Array([1, 2, 3]).buffer"),
              expected);
}

TEST_F(PyDukContext, simple_object_conversion) {
    boost::python::dict expected;
    expected["hello"] = "world";
    expected["key"] = 2;
    EXPECT_EQ(context.run("var d = {hello: 'world', key: 2}; d;"),
              expected);
}

TEST_F(PyDukContext, complex_object_conversion) {
    boost::python::dict expected;
    boost::python::dict inner;
    boost::python::list list;
    expected["hello"] = "world";
    expected["inner"] = inner;
    inner["key"] = "value";
    inner["list"] = list;
    list.append(1);
    list.append(2.2);
    list.append(3.0);
    EXPECT_EQ(context.run("var d = {hello: 'world', inner: {key: 'value', list: [1, 2.2, 3.0]}}; d;"),
              expected);
}

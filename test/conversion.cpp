#include <gtest/gtest.h>
#include "context_fixture.hpp"
#include <boost/python.hpp>

TEST_F(PyDukContext, string_conversion) {
    EXPECT_EQ(context->run("'Hello, World!'"),
              boost::python::object("Hello, World!"));
}

TEST_F(PyDukContext, integer_conversion) {
    auto actual = context->run("1 + 2");
    EXPECT_EQ(PyLong_Check(actual.ptr()),
              true);
    EXPECT_EQ(actual,
              boost::python::object(3));
}

TEST_F(PyDukContext, number_conversion) {
    EXPECT_EQ(context->run("1.2 + 2.3"),
              boost::python::object(3.5));
}

TEST_F(PyDukContext, boolean_conversion) {
    EXPECT_EQ(context->run("true"),
              boost::python::object(true));
}

TEST_F(PyDukContext, boolean_object_conversion) {
    EXPECT_EQ(context->run("new Boolean(1)"),
              boost::python::object(true));
}

TEST_F(PyDukContext, empty_object_conversion) {
    boost::python::dict expected;
    EXPECT_EQ(context->run("var d = {}; d;"),
              expected);
}

TEST_F(PyDukContext, empty_list_conversion) {
    boost::python::list expected;
    EXPECT_EQ(context->run("var d = []; d;"),
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
    EXPECT_EQ(context->run("var d = [1, 2.0, 'hello', ['inner', 'list']]; d;"),
              expected);
}

TEST_F(PyDukContext, number_object) {
    EXPECT_EQ(context->run("new Number(12.0)"),
              boost::python::object(12));
}

TEST_F(PyDukContext, number_object_float) {
    EXPECT_EQ(context->run("new Number(12.4)"),
              boost::python::object(12.4));
}

TEST_F(PyDukContext, array_buffer_conversion) {
    EXPECT_EQ(context->run("new Int8Array([258, 2, 0, -2]).buffer"),
              boost::python::handle<>(PyByteArray_FromStringAndSize("\x02\x02\x00\xfe", 4)));
}

TEST_F(PyDukContext, uint8_array_conversion) {
    EXPECT_EQ(context->run("new Uint8Array([258, 2, 0, -2]).buffer"),
              boost::python::handle<>(PyByteArray_FromStringAndSize("\x02\x02\x00\xfe", 4)));
}

TEST_F(PyDukContext, int8_array_conversion) {
    EXPECT_EQ(context->run("new Int8Array([130, -2, 3, 256, 0, 1])"),
              boost::python::handle<>(PyByteArray_FromStringAndSize("\x82\xfe\x03\x00\x00\x01", 6)));
}

TEST_F(PyDukContext, uint16_array_conversion) {
    EXPECT_EQ(context->run("new Uint16Array([256, -1])"),
              boost::python::handle<>(PyByteArray_FromStringAndSize("\x00\x01\xff\xff", 4)));
}

TEST_F(PyDukContext, int16_array_conversion) {
    EXPECT_EQ(context->run("new Int16Array([256, -1])"),
              boost::python::handle<>(PyByteArray_FromStringAndSize("\x00\x01\xff\xff", 4)));
}

TEST_F(PyDukContext, uint32_array_conversion) {
    EXPECT_EQ(context->run("new Uint32Array([65536, -1])"),
              boost::python::handle<>(PyByteArray_FromStringAndSize("\x00\x00\x01\x00\xff\xff\xff\xff", 8)));
}

TEST_F(PyDukContext, int32_array_conversion) {
    EXPECT_EQ(context->run("new Int32Array([65536, -1])"),
              boost::python::handle<>(PyByteArray_FromStringAndSize("\x00\x00\x01\x00\xff\xff\xff\xff", 8)));
}


TEST_F(PyDukContext, float32_array_conversion) {
    EXPECT_EQ(context->run("new Float32Array([12.3])"),
              boost::python::handle<>(PyByteArray_FromStringAndSize("\xcd\xcc\x44\x41", 4)));
}

TEST_F(PyDukContext, float64_array_conversion) {
    EXPECT_EQ(context->run("new Float64Array([12.3])"),
              boost::python::handle<>(PyByteArray_FromStringAndSize("\x9a\x99\x99\x99\x99\x99\x28\x40", 8)));
}
TEST_F(PyDukContext, simple_object_conversion) {
    boost::python::dict expected;
    expected["hello"] = "world";
    expected["key"] = 2;
    EXPECT_EQ(context->run("var d = {hello: 'world', key: 2}; d;"),
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
    EXPECT_EQ(context->run("var d = {hello: 'world', inner: {key: 'value', list: [1, 2.2, 3.0]}}; d;"),
              expected);
}

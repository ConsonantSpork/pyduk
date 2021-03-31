#pragma once

#include <gtest/gtest.h>
#define BOOST_BIND_GLOBAL_PLACEHOLDERS  // suppress boost compile-time warning
#include <boost/python.hpp>

class PyDukEnvironment : public testing::Environment {
    protected:
        void SetUp() {
            Py_Initialize();
        }
};

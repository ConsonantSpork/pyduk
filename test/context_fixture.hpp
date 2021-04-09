#pragma once

#include <gtest/gtest.h>
#include <context.hpp>
#include "context_fixture.hpp"

class PyDukContext : public ::testing::Test {
    protected:
        pyduk::Context* context;
        void SetUp() {
            context = new pyduk::Context(0);
        }
        void TearDown() {
            delete context;
        }
};

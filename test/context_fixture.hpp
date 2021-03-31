#pragma once

#include <gtest/gtest.h>
#include <context.hpp>
#include "context_fixture.hpp"

class PyDukContext : public ::testing::Test {
    protected:
        pyduk::Context context;
};

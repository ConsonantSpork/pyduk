#include <gtest/gtest.h>
#include "environment.hpp"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(new PyDukEnvironment());
    return RUN_ALL_TESTS();
}

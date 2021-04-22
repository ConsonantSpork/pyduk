find_package(GTest)
if(${GTest_FOUND})
  add_executable(gtest
          main.cpp
          conversion.cpp
          context_fixture.hpp
          environment.hpp
          circular_references.cpp)

  get_target_property(PYDUK_SOURCE_DIR pyduk SOURCE_DIR)
  target_include_directories(gtest
          PRIVATE
          ${GTest_INCLUDE_DIRS}
          ${PYDUK_SOURCE_DIR}  # Need to get into inner workings of library
          # to test properly
          )
  target_link_libraries(gtest
          PRIVATE
          ${GTEST_LIBRARIES}
          pyduk
          )

  enable_testing()
  gtest_add_tests(TARGET gtest)
endif()

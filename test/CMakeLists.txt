find_package(GTest)
if(${GTest_FOUND})
  add_executable(gtest
    main.cpp
    test.cpp
    )
  target_include_directories(gtest
    PRIVATE
    ${GTest_INCLUDE_DIRS}
    )
  target_link_libraries(gtest
    ${GTEST_LIBRARIES}
    )

  enable_testing()
  gtest_add_tests(TARGET gtest)
endif()

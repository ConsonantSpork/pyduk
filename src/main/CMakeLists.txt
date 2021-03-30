add_executable(main main.cpp)
target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(main PRIVATE duktape)

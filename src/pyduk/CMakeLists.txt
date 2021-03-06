find_package(Boost COMPONENTS python3 REQUIRED)
find_package(PythonLibs REQUIRED)
add_library(pyduk SHARED
        pyduk.cpp
        pyduk.hpp.in
        context.cpp
        context.hpp
        exceptions.cpp
        exceptions.hpp
        i_circular_reference_tracker.hpp
        circular_reference_tracker.hpp)

set(MODULE_PREFIX "_")
set_target_properties(pyduk PROPERTIES
        PREFIX ${MODULE_PREFIX}
        )
set(PYTHON_MODULE_NAME "${MODULE_PREFIX}${CMAKE_PROJECT_NAME}")
set(PYTHON_MODULE_VERSION_MINOR ${pyduk_VERSION_MINOR})
set(PYTHON_MODULE_VERSION_MAJOR ${pyduk_VERSION_MAJOR})
configure_file(pyduk.hpp.in pyduk.hpp @ONLY)

get_target_property(DUKTAPE_SOURCE_DIR duktape SOURCE_DIR)
target_include_directories(pyduk
        PUBLIC
        ${DUKTAPE_SOURCE_DIR}
        ${Boost_INCLUDE_DIRECTORIES}
        ${PYTHON_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}  # for configured header file pyduk.hpp
        )
target_link_libraries(pyduk
        PUBLIC
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARY}
        duktape
        )

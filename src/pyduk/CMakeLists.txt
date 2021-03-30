find_package(Boost COMPONENTS python REQUIRED)
find_package(PythonLibs REQUIRED)
add_library(pyduk SHARED pyduk.cpp)

set(PYTHON_MODULE_NAME ${CMAKE_PROJECT_NAME})
set(PYTHON_MODULE_VERSION_MINOR ${pyduk_VERSION_MINOR})
set(PYTHON_MODULE_VERSION_MAJOR ${pyduk_VERSION_MAJOR})
configure_file(pyduk.hpp.in pyduk.hpp @ONLY)

set_target_properties(pyduk PROPERTIES
  PREFIX ""
  )

target_include_directories(pyduk
  PUBLIC
  ${Boost_INCLUDE_DIRECTORIES}
  ${PYTHON_INCLUDE_DIRS}
  PRIVATE
  ${PROJECT_SOURCE_DIR}/lib/
  ${PROJECT_BINARY_DIR}/src/pyduk
  )
target_link_libraries(pyduk
  PRIVATE
  ${Boost_PYTHON_LIBRARY}
  ${Python_LIBRARIES}
  duktape
  )

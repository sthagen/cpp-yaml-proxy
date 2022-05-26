cmake_minimum_required(VERSION 3.7...3.23)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# ---- Project ----

project(yaml_proxy LANGUAGES CXX)

option(YAML_EXAMPLES "whether or not to build the examples" ON)

# ---- Fetch CPM ----

set(CPM_DOWNLOAD_VERSION 0.27.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake v${CPM_DOWNLOAD_VERSION}")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# ---- Add dependencies via CPM ----
# See https://github.com/TheLartians/CPM.cmake for details and examples

CPMAddPackage(
  NAME yaml-cpp
  GIT_REPOSITORY https://github.com/sthagen/jbeder-yaml-cpp.git
  VERSION 0.6.4                                  
  # 0.6.4 is not released yet, so use the latest approved commit
  GIT_TAG 98acc5a8874faab28b82c28936f4b400b389f5d6 
  OPTIONS
    "YAML_CPP_BUILD_TESTS Off"
    "YAML_CPP_BUILD_CONTRIB Off"
    "YAML_CPP_BUILD_TOOLS Off"
)

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY sthagen/doctest
  GIT_TAG 2020.12
)

# ---- Create binary ----

add_executable(yaml_test main.cpp)
target_link_libraries(yaml_test doctest yaml-cpp)
set_target_properties(yaml_test PROPERTIES CXX_STANDARD 17)

# ---- Enable testing ----

enable_testing() 
add_test(yaml_test yaml_test)

# ---- Create the examples ----

message(STATUS "Note the fetched includes are taken from below: ${FETCHCONTENT_BASE_DIR}")
if (YAML_EXAMPLES)
    macro(yaml_examples EXAMPLENAME)
        add_executable(${EXAMPLENAME} ${ARGN})
        set_target_properties(${EXAMPLENAME} PROPERTIES FOLDER examples)
        set_target_properties(${EXAMPLENAME} PROPERTIES CXX_STANDARD 17)
        target_include_directories(${EXAMPLENAME} PUBLIC "${FETCHCONTENT_BASE_DIR}/yaml-cpp-src/include/")
        add_test(NAME ${EXAMPLENAME} COMMAND ${EXAMPLENAME})
    endmacro()
    add_subdirectory(examples)
endif()

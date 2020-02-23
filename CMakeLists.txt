cmake_minimum_required(VERSION 3.1.2)
project(graph_search)

set (CMAKE_CXX_STANDARD 17)
add_compile_definitions(RANGES_DEEP_STL_INTEGRATION)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB sources graph_search/*.cpp)
add_executable(${PROJECT_NAME} ${sources})

include_directories("graph_search")

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
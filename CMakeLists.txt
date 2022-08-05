cmake_minimum_required(VERSION 3.5.1)

set (CMAKE_CXX_STANDARD 17)

project (xxhash-node-cmake)

include_directories(${CMAKE_JS_INC} /usr/local/lib/node_modules/nan)

file(GLOB SOURCE_FILES "src/*.cc" "src/*.h" "xxhash/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

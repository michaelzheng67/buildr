add_library(roles STATIC admin.cpp client.cpp)
target_include_directories(roles PUBLIC "${CMAKE_SOURCE_DIR}/include")
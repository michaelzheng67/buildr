add_library(state STATIC log_manager.cpp)
target_include_directories(state PUBLIC "${CMAKE_SOURCE_DIR}/include")
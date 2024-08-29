add_library(utils STATIC os.cpp)
target_include_directories(utils PUBLIC "${CMAKE_SOURCE_DIR}/include")
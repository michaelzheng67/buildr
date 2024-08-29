add_library(resource STATIC cgroup.cpp linux_namespace.cpp)
target_include_directories(resource PUBLIC "${CMAKE_SOURCE_DIR}/include")
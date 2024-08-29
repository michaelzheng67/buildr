#ifndef LINUX_NAMESPACE_HPP 
#define LINUX_NAMESPACE_HPP

#include <string>

namespace linux_namespace {

    int setup_user_process(std::string socket_path);
}

#endif
#ifndef LOG_MANAGER_HPP 
#define LOG_MANAGER_HPP

#include "roles/admin.hpp"
#include <map>
#include <unordered_set>
#include <list>
#include <optional>


namespace log_manager {

    const std::string _FILE_PATH="/tmp/buildr_log/state.txt";

    void save_state(admin::admin admin);

    admin::admin restore_state();

}

#endif
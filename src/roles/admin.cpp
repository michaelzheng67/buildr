#include "roles/admin.hpp"
#include "resource/linux_namespace.hpp"
#include <iostream>
#include <unistd.h>

// Namespace implementation
namespace admin {

    admin::admin() {}

    admin::~admin() {}

    void admin::add_user(client::client user) {
        // if name already exists, let admin know.
        if (this->users.count(user.get_name()) != 0) {
            std::cout << "User already exists" << std::endl;
            return;
        }

        int pid = linux_namespace::setup_user_process("");

        // place pid into corresponding cgroups

        this->users.insert(user.get_name());
        this->user_namespaces[user.get_name()] = pid;
        
    }

    void admin::remove_user(client::client user) {
        this->user_namespaces.erase(user.get_name());
        this->user_cgroups.erase(user.get_name());
        this->user_sockets.erase(user.get_name());
        this->users.erase(user.get_name());
    }

    std::unordered_set<std::string> admin::get_users() {
        return this->users;
    }

    void admin::set_resources(std::map<std::string, int> resources) {
        this->resources = resources;  
    }

    void admin::execute_user_command(std::string user, std::string command) {
        int user_fd = this->user_fds[user];
        write(user_fd, command.c_str(), strlen(command.c_str()));
    }

    void admin::view_stats() {
        std::cout << "Buildr stats" << std::endl;
        std::cout << "Users:" << std::endl;
        for (const std::string user : this->users) {
            std::cout << user << std::endl;
        }
    }

    void admin::view_summary_ui() {
        
    }

}
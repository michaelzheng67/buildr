#ifndef ADMIN_HPP 
#define ADMIN_HPP

#include "roles/client.hpp"
#include <map>
#include <unordered_set>
#include <list>
#include <sys/un.h>

namespace admin {

    // Entity that controls the entire setup for all other users.
    class admin {
    private:
        std::map<std::string, int> user_namespaces;
        std::map<std::string, std::list<std::string>> user_cgroups; 
        std::map<std::string, sockaddr_un> user_sockets;
        std::map<std::string, int> user_fds;
        std::unordered_set<std::string> users;
        std::map<std::string, int> resources;
    public:
       
        admin();

        ~admin();

        void add_user(client::client user);

        void remove_user(client::client user);

        std::unordered_set<std::string> get_users();

        void set_resources(std::map<std::string, int> resources);

        void execute_user_command(std::string user, std::string command);

        void view_stats();

        void view_summary_ui();

    };

}

#endif
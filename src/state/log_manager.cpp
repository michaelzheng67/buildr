#include "state/log_manager.hpp"
#include "roles/admin.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>

void ensure_directory_exists(const std::string& path) {
    struct stat info;

    if (stat(path.c_str(), &info) != 0) {
        if (mkdir(path.c_str(), 0755) != 0) {
            std::cerr << "Error creating directory " << path << ": " << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }
    } else if (!(info.st_mode & S_IFDIR)) {
        std::cerr << path << " exists but is not a directory." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void log_manager::save_state(admin::admin admin) {

    // TODO: BAD PATTERN. Let's try to fix this so that we just
    // have to change _FILE_PATH for the directory_path to be changed
    // as well.
    std::string directory_path = "/tmp/buildr_log";
    ensure_directory_exists(directory_path);

    std::ofstream file;
    file.open(log_manager::_FILE_PATH);
    
    file << "users\n";

    for (const std::string & user : admin.get_users()) {
        file << user << " ";
    }
    file << "\n";

    file.close();

}

std::vector<std::string> split_string_by_space(const std::string & line) {
    std::vector<std::string> result;
    std::istringstream iss(line);
    std::string word;
    
    while (iss >> word) {
        result.push_back(word);
    }
    
    return result;
}


admin::admin log_manager::restore_state() {
    
    admin::admin admin;
    std::ifstream file(log_manager::_FILE_PATH);

    if (!file.is_open()) {
        std::cout << "state file unable to be opened" << std::endl;
        return admin;
    }

    std::string line;
    int user_line = -1;

    int curr = 0;
    while (std::getline(file, line)) {
        curr++;

        // 'user' was the last line, so this one must have user object info
        if (user_line + 1 == curr) {
            std::vector<std::string> users = split_string_by_space(line);
            for (const std::string & user : users) {
                admin.add_user(user);
            }
        }

        if (line == "users") {
            user_line = curr;
        }
    }

    file.close();
    return admin;

}
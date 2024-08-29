#include "utils/os.hpp"
#include <string>
#include <unistd.h>
#include <sys/wait.h>

int os::create_task(std::string command, std::string args) {
    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        return 1;
    } else if (pid == 0) {
        // Child process
        char* args_arr[] = {strdup(command.c_str()), strdup(args.c_str()), NULL};
        execvp(args_arr[0], args_arr);
        // If execvp returns, it must have failed
        return 1;
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            // exit with status
            return status;
        } else {
            // failure
            return 1;
        }
    }
}

sockaddr_un os::create_unix_socket_server(std::string file_path) {

}

void os::create_unix_socket_client(sockaddr_un server_addr) {
    
}
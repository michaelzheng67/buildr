#define _GNU_SOURCE
#include "resource/linux_namespace.hpp"

#include <iostream> 
#include <sched.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

void _accept_socket_commands(std::string socket_path) {
    // Allow calling process to begin executing commands from socket connection.
    int sock = 0;
    struct sockaddr_un serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, socket_path.c_str(), sizeof(serv_addr.sun_path) - 1);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sock);
        return;
    }

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        int valread = read(sock, buffer, sizeof(buffer) - 1);
        if (valread < 0) {
            std::cerr << "Failed to read from socket" << std::endl;
            break;
        } else if (valread == 0) {
            std::cout << "Server closed the connection" << std::endl;
            break;
        }

        buffer[valread] = '\0';
        std::cout << "Received command: " << buffer << std::endl;

        int ret = system(buffer);
        if (ret == -1) {
            std::cerr << "Failed to execute command" << std::endl;
        } else {
            std::cout << "Command executed successfully with return code: " << ret << std::endl;
        }
    }

    close(sock);
}

int linux_namespace::setup_user_process(std::string socket_path) {
    // This function creates the user object process. It accomplishes this by spawning
    // a child process and ensuring:
    //   (1) The process is namespaced properly
    //   (2) The process is ready to begin accepting commands from its parent process
    //
    // returns the pid of the child that was created.
    
    // part (1)
    // pid_t pid = clone(child_func, child_stack + STACK_SIZE, 
    //                   CLONE_NEWPID | CLONE_NEWUTS | SIGCHLD, NULL);
    pid_t pid;

    if (pid == -1) { 
        perror("fork"); 
        exit(EXIT_FAILURE);

    } else if (pid == 0) {
        // part (2)
        _accept_socket_commands(socket_path);
    
    } else if (pid > 0) { 
        // can't have pid == 1 since that's the init process so HIGHLY UNLIKELY
        // that there is a collision with the fork returning failure (i.e. a return
        // value of 1 from this function means it failed)
        return pid;
    }
  
    return 0;
}

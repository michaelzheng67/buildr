#ifndef OS_HPP
#define OS_HPP

#include<string>
#include <sys/un.h>

namespace os {

    // returns status code of command once process terminates.
    int create_task(std::string command, std::string args);

    sockaddr_un create_unix_socket_server(std::string file_path);
    
    void create_unix_socket_client(sockaddr_un server_addr);

    

}

#endif
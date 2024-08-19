#ifndef ADMIN_HPP 
#define ADMIN_HPP

#include <map>

namespace admin {

    // Entity that controls the entire setup for all other users.
    class admin {
    private:
        

    public:
       
        // constructor
        admin();

        // Destructor
        ~admin();

        // add user
        void addUser();

        // remove user
        void removeUser();

        // default resource settings
        void resourceSettings(std::map<std::string, int> resources);

    };

}

#endif
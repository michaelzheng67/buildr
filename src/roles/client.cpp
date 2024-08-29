#include "roles/client.hpp"

// Namespace implementation
namespace client {

    client::client(std::string name) : name(name) {}

    client::~client() {
    }
    
    std::string client::get_name() const {
        return this->name;
    }

    void client::set_name(std::string name) {
        this->name = name;
    }

}
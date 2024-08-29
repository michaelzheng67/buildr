#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <unordered_set>

namespace client {

    // A user entity.
    class client {
    private:
        std::string name;
        std::unordered_set<int> process_ids;

    public:
       
        client(std::string name);

        ~client();

        std::string get_name() const;

        void set_name(std::string name);

        bool operator==(const client& other) const {
            return this->name == other.name;
        }
    };
}

namespace std {
    template <>
    struct hash<client::client> {
        std::size_t operator()(const client::client& c) const {
            return std::hash<std::string>()(c.get_name());
        }
    };
}

#endif
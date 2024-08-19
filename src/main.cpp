#include <iostream>
#include <string>
#include <vector>

// Function to print usage information
void print_usage() {
    std::cout << "Usage: buildr [options] [arguments]\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help      Show this help message and exit\n";
    std::cout << "Examples:\n";
    std::cout << " buildr --help\n";
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::vector<std::string> args(argv, argv + argc);

    // Iterate over command-line arguments
    for (size_t i = 1; i < args.size(); ++i) {
        std::string arg = args[i];

        if (arg == "-h" || arg == "--help") {
            print_usage();
            return 0;
        } else {
            std::cerr << "Unknown argument: " << arg << "\n";
            print_usage();
            return 1;
        }
    }

    return 0;
}

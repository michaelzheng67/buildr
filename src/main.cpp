#include "CLI/CLI.hpp"
#include "roles/admin.hpp"
#include "roles/client.hpp"
#include "state/log_manager.hpp"
#include "utils/os.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {

    /* Argument parser */
    CLI::App app{"Buildr - Linux resource management through your cli"};
    
    /* ADMIN COMMANDS */
    auto admin_cmd = app.add_subcommand("admin", "Run Buildr as admin.");

    auto save_state_cmd = admin_cmd->add_subcommand("save_state", "Save state of user objects.");

    auto restore_state_cmd = admin_cmd->add_subcommand("restore_state", "Restore state of user objects.");

    auto create_user_cmd = admin_cmd->add_subcommand("create_user", "Create a new user.");
    std::string user_name;
    create_user_cmd->add_option("-n,--name", user_name, "Username")->required();

    auto remove_user_cmd = admin_cmd->add_subcommand("remove_user", "Remove a user by name.");
    std::string remove_user_name;
    remove_user_cmd->add_option("-n,--name", remove_user_name, "Username")->required();

    auto view_stats_cmd = admin_cmd->add_subcommand("view_stats", "Summary of admin settings within cli.");

    auto view_summary_ui = admin_cmd->add_subcommand("view_summary_ui", "Open stats UI in web browser.");

    auto set_resources_cmd = admin_cmd->add_subcommand("set_resources", "Set default resources for all users.");
    int cpu;
    int mem;
    set_resources_cmd->add_option("-c,--cpu", cpu, "CPU allowed per user.")->required();
    set_resources_cmd ->add_option("-m,--mem", mem, "Memory allowed per user.")->required();
    std::map<std::string, int> resource_mapping;
    resource_mapping["cpu"] = cpu;
    resource_mapping["mem"] = mem;


    /* USER COMMANDS */
    auto user_cmd = app.add_subcommand("user", "Run Buildr as user.");

    auto user_run_cmd = user_cmd->add_subcommand("run", "Run task.");
    std::string user_name_task;
    std::string user_task;

    user_run_cmd->add_option("-u,--user", user_name_task, "Run as user.")->required();
    user_run_cmd->add_option("-t,--task", user_task, "Task to run.")->required();

    CLI11_PARSE(app, argc, argv);

    /* Initialization */
    admin::admin admin;
    sockaddr_un server_addr = os::create_unix_socket_server("/run/buildr");
        
    std::cout << "Buildr - cli-based linux resource management tool" << std::endl;
    while (true) {
        std::cout << "command: ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "") continue;
        if (input == "exit" || input == "quit") break;

        try {
            app.parse(input, false);

            if (admin_cmd->parsed()) {

                if (save_state_cmd->parsed()) {
                    log_manager::save_state(admin);

                } else if (restore_state_cmd->parsed()) {
                    admin = log_manager::restore_state();

                } else if (create_user_cmd->parsed()) {
                    client::client user(user_name);
                    admin.add_user(user);

                } else if (remove_user_cmd->parsed()) {
                    admin.remove_user(remove_user_name);

                } else if (view_stats_cmd->parsed()) {
                    admin.view_stats();

                } else if (view_summary_ui->parsed()) {
                    admin.view_summary_ui();
                
                } else if (set_resources_cmd->parsed()) {
                    admin.set_resources(resource_mapping);
                }

            } else if (user_cmd->parsed()) {

                if (user_run_cmd->parsed()) {
                    admin.execute_user_command(user_name_task, user_task);
                }
            }
        } catch (const CLI::CallForHelp& e) {
            std::cout << app.help() << std::endl;

        } catch (const CLI::ParseError &e) {
            std::cerr << app.exit(e) << std::endl;
        }
    }

    return 0;
}

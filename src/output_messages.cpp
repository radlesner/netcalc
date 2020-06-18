#include "headers/output_messages.h"

void version_program() { std::cout << "netcalc, version " << VERSION_PROGRAM << std::endl; }

void output_ip_address(const std::string &label, std::vector<unsigned int> input, const std::string &extra_label)
{
    std::cout << label;

    for (size_t i = 0; i < input.size(); i++)
    {
        std::cout << input[i];

        if (i == (input.size() - 1))
        {
            if (extra_label != "") std::cout << "/" << extra_label;
            std::cout << std::endl;
        }
        else
            std::cout << ".";
    }
}

void help_panel()
{
    std::cout << "Usage: netcalc [ip_v4_address] [prefix_netmask]" << std::endl
              << "Options:" << std::endl
              << "    -i    --inteface    Calculates values from interface" << std::endl
              << "    -v    --version     Version program" << std::endl
              << "    -h    --help        Help panel" << std::endl;
}

void usage_message() { std::cout << "Usage: netcalc [ip_v4_address] [prefix_netmask] or -h option" << std::endl; }
void error_message() { std::cout << "Bad ip address or prefix" << std::endl; }

void error_message_argument(const std::string &argument_input)
{
    std::cout << "Bad argument " << argument_input << std::endl << "Use -h or --help to display help" << std::endl;
}
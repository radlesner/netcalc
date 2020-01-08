#include "headers/output_messages.h"

void version_program()
{
    // Version of program must be changed in snapcraft.yaml file
    std::cout << "netcalc, version " << VERSION_PROGRAM << std::endl;
}

void output_ip_address(std::string label, std::vector<unsigned int> input)
{
    std::cout << label;

    for (size_t i = 0; i < input.size(); i++)
    {
        std::cout << input[i];

        if (i == input.size() - 1)
            std::cout << std::endl;
        else
            std::cout << ".";
    }
}

void help_panel()
{
    std::cout << "Usage: netcalc [ip_v4_address] [prefix_netmask]" << std::endl
              << "    -i    --inteface    Calculates values from interface" << std::endl
              << "    -v    --version     Show version of program" << std::endl
              << "    -h    --help        Help panel" << std::endl;
}

void usage_message() { std::cout << "Usage: netcalc [ip_v4_address] [prefix_netmask]" << std::endl; }
void error_message() { std::cout << "Bad ip address or prefix" << std::endl; }

void error_message_argument(char *argument_input)
{
    std::cout << "Bad argument " << argument_input << std::endl
              << "Use -h or --help to display help" << std::endl;
}
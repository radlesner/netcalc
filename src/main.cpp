#include <iostream>
#include <cstring>

#include "headers/check_ip.h"
#include "headers/check_prefix.h"
#include "headers/netmask.h"
#include "headers/octet.h"
#include "headers/convert_numbers.h"
#include "headers/ip_operations.h"
#include "headers/get_network_addresses.h"
#include "headers/output.h"

int main(int argc, char **argv)
{
	if(argc > 2)
	{
        if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--inteface"))
        {
            get_network(argv[2]);
        }
        else
        {
            std::string
                ip_address = argv[1],
                prefix_netmask = argv[2],
                binary_ip_address,
                binary_ip_octet[4],
                binary_netmask,
                binary_network,
                binary_broadcast,
                valid_ip_color_monit[2] = { "\033[0m\033[1;32m", "\033[0m" };

            int ip_octet[4];

            bool
                valid_prefix,
                valid_ip;

            valid_prefix = is_valid_netmask_prefix(prefix_netmask);
            if (valid_prefix == false)
            {
                error_message();
                usage_message();
                return 1;
            }

            valid_ip = is_valid_ip(argv[1]);
            if (valid_ip == true)
            {
                std::cout
                    << "IP address:        " << ip_address
                    << " (" << valid_ip_color_monit[0] << "OK" << valid_ip_color_monit[1] << ")" << std::endl;
            }
            else
            {
                error_message();
                usage_message();
                return 1;
            }

            for (int i = 0; i < 4; i++)
            {
                ip_octet[i] = std::stoi(division_on_octet(ip_address, i));
                binary_ip_octet[i] = dec_to_bin(ip_octet[i]);
                binary_ip_address += binary_ip_octet[i];
            }

            binary_netmask = make_netmask(prefix_netmask);
            binary_network = get_network_address(binary_ip_address, binary_netmask);
            binary_broadcast = get_broadcast_addr(binary_network, binary_netmask);
            get_number_hosts(binary_ip_address, prefix_netmask);
            get_first_last_host(binary_network, binary_broadcast);
        }
	}
    else if (argc > 1)
    {
        if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))
        {
            version_program();
        }
        else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
        {
            help_panel();
        }
        else if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--inteface"))
        {
            show_interfaces();
        }
        else
        {
            error_message_argument(argv[1]);
        }
    }
    else
    {
        usage_message();
    }

    return 0;
}
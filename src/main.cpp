#include <iostream>
#include <cstring>

#include "check_ip.h"
#include "check_prefix.h"
#include "netmask.h"
#include "octet.h"
#include "convert_numbers.h"
#include "ip_operations.h"

int main(int argc, char **argv)
{
	if(argc > 2)
	{
        std::string ip_address = argv[1],
                    prefix_netmask = argv[2],

                    binary_ip_address,
                    binary_ip_octet[4],
                    binary_netmask,
                    binary_network,
                    binary_broadcast;

        int ip_octet[4],
            valid_ip;

        bool valid_prefix;

        valid_prefix = is_valid_netmask_prefix(prefix_netmask);
        if (valid_prefix == false)
        {
            std::cout << "Bad prefix netmask" << std::endl
                      << "Usage: netcalc [ip_v4_address] [prefix_netmask]" << std::endl;
            return 1;
        }

        valid_ip = is_valid_ip(argv[1]);
        if (valid_ip == 1)
        {
            std::cout << "IP address:        " << ip_address << " (\033[0m\033[1;32mOK\033[0m)" << std::endl;
        }
        else
        {
            std::cout << "Bad ip address" << std::endl
                      << "Usage: netcalc [ip_v4_address] [prefix_netmask]" << std::endl;
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
    else
    {
        std::cout << "Usage: netcalc [ip_v4_address] [prefix_netmask]" << std::endl;
    }

    return 0;
}
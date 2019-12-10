#include <iostream>
#include <cstring>

#include "check_ip.h"
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

        int ip_octet[4];

        if ((static_cast<int>(prefix_netmask[0]) >= 48 && static_cast<int>(prefix_netmask[0]) <= 57) &&
            (static_cast<int>(prefix_netmask[1]) >= 48 && static_cast<int>(prefix_netmask[1]) <= 57))
        {
            if (std::stoi(prefix_netmask) < 0 || std::stoi(prefix_netmask) > 31)
            {
                std::cout << "Bad prefix netmask" << std::endl;
                return 1;
            }
        }
        else
        {
            std::cout << "You must enter a value in numbers" << std::endl;
            return 1;
        }



        if (is_valid_ip(argv[1]) == 1)
        {
            std::cout << "IP address: " << ip_address << " (OK)" << std::endl;
        }
        else
        {
            std::cout << "IP address: " << ip_address << " (WRONG)" << std::endl;
            return 1;
        }

        for (int i = 0; i < 4; i++)
        {
            ip_octet[i] = std::stoi(division_on_octet(ip_address, i));
            binary_ip_octet[i] = dec_to_bin(ip_octet[i]);
            binary_ip_address += binary_ip_octet[i];
        }

        std::cout << std::endl;

        binary_netmask = make_netmask(prefix_netmask);
        binary_network = get_network_address(binary_ip_address, binary_netmask);
        binary_broadcast = get_broadcast_addr(binary_network, binary_netmask);
        get_number_hosts(binary_ip_address, prefix_netmask);
        get_first_last_host(binary_network, binary_broadcast);
	}
    else
    {
        std::cout << "help panel" << std::endl;
    }

    return 0;
}
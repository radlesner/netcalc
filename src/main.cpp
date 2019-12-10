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
                    binary_netmask,

                    binary_ip_octet[4];

        int ip_octet[4];

        if (std::stoi(prefix_netmask) < 0 || std::stoi(prefix_netmask) > 31)
        {
            std::cout << "Bad prefix netmask" << std::endl;
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


        binary_netmask = make_netmask(prefix_netmask);
        get_network_address(binary_ip_address, binary_netmask);
	}
    else
    {
        std::cout << "help panel" << std::endl;
    }

    return 0;
}
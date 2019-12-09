#include <iostream>
#include <cstring>

#include "check_ip.h"
#include "octet.h"
#include "convert_numbers.h"
#include "ip_operations.h"

int main(int argc, char **argv)
{
	if(argc > 2)
	{
        std::string ip_address = argv[1],
                    netmask = argv[2],

                    binary_ip_address,
                    binary_netmask,

                    binary_ip_octet[4],
                    binary_netmask_octet[4];

        int ip_octet[4],
            netmask_octet[4];


        if (is_valid_ip(argv[1]) == 1) std::cout << "IP address: " << ip_address << " (OK)" << std::endl;
        else                           std::cout << "IP address: " << ip_address << " (WRONG)" << std::endl;

        if (is_valid_ip(argv[2]) == 1) std::cout << "Netmask: " << netmask << " (OK)" << std::endl;
        else                           std::cout << "Netmask: " << netmask << " (WRONG)" << std::endl << std::endl;


        for (size_t i = 0; i < 4; i++)
        {
            ip_octet[i] = std::stoi(division_on_octet(ip_address, i));
            netmask_octet[i] = std::stoi(division_on_octet(netmask, i));

            binary_ip_octet[i] = std::to_string(dec_to_bin(ip_octet[i]));
            binary_netmask_octet[i] = std::to_string(dec_to_bin(netmask_octet[i]));

            if (binary_ip_octet[i] == "0")
            {
                binary_ip_octet[i] = "00000000";
            }

            if (binary_netmask_octet[i] == "0")
            {
                binary_netmask_octet[i] = "00000000";
            }

            if (binary_ip_octet[i].length() < 8)
            {
                do
                {
                    binary_ip_octet[i] = "0" + binary_ip_octet[i];
                } while (binary_ip_octet[i].length() != 8);
            }

            if (binary_netmask_octet[i].length() < 8)
            {
                do
                {
                    binary_netmask_octet[i] = "0" + binary_netmask_octet[i];
                } while (binary_netmask_octet[i].length() != 8);
            }

            binary_ip_address += binary_ip_octet[i];
            binary_netmask += binary_netmask_octet[i];
        }

        get_network_address(binary_ip_address, binary_netmask);







        // std::cout << binary_ip_octet[0] << "."
        //           << binary_ip_octet[1] << "."
        //           << binary_ip_octet[2] << "."
        //           << binary_ip_octet[3] << std::endl;

        // std::cout << binary_ip_address << std::endl;
        // std::cout << binary_ip_address.length() << std::endl;

        // std::cout << binary_netmask_octet[0] << "."
        //           << binary_netmask_octet[1] << "."
        //           << binary_netmask_octet[2] << "."
        //           << binary_netmask_octet[3] << std::endl;

        // std::cout << binary_netmask << std::endl;
        // std::cout << binary_netmask.length() << std::endl;
	}
    else
    {
        std::cout << "help panel" << std::endl;
    }
}
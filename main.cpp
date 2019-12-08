#include <iostream>
#include <cstring>

#include "check_ip.h"
#include "octet.h"

int main(int argc, char **argv)
{
	if(argc > 2)
	{
        std::string ip_address = argv[1],
                    netmask = argv[2],
                    ip_octet[4],
                    netmask_octet[4];


        if (is_valid_ip(argv[1]) == 1) std::cout << "IP address: " << ip_address << " OK" << std::endl;
        else                           std::cout << "IP address: " << ip_address << " WRONG" << std::endl;

        if (is_valid_ip(argv[2]) == 1) std::cout << "Netmask: " << netmask << " OK" << std::endl;
        else                           std::cout << "Netmask: " << netmask << " WRONG" << std::endl << std::endl;


        for (size_t i = 0; i < 4; i++)
        {
            ip_octet[i] = division_on_octet(ip_address, i);
        }

        for (size_t i = 0; i < 4; i++)
        {
            netmask_octet[i] = division_on_octet(netmask, i);
        }


        std::cout << ip_octet[0] << " ; "
                  << ip_octet[1] << " ; "
                  << ip_octet[2] << " ; "
                  << ip_octet[3] << std::endl;

        std::cout << netmask_octet[0] << " ; "
                  << netmask_octet[1] << " ; "
                  << netmask_octet[2] << " ; "
                  << netmask_octet[3] << std::endl;
	}
    else
    {
        std::cout << "help panel" << std::endl;
    }
}
#include <iostream>
#include <cstring>

#include "check_ip.h"

int main(int argc, char **argv)
{
	if(argc > 2)
	{
        if (is_valid_ip(argv[1]) == 1)    std::cout << "IP address: OK" << std::endl;
        else                              std::cout << "IP address: WRONG" << std::endl;

        if (is_valid_ip(argv[2]) == 1)    std::cout << "Mask address: OK" << std::endl;
        else                              std::cout << "Mask address: WRONG" << std::endl;

	}
    else
    {
        std::cout << "help panel" << std::endl;
    }
}
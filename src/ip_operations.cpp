#include "check_ip.h"
#include "octet.h"
#include "convert_numbers.h"
#include "ip_operations.h"

void get_network_address(std::string ip4_addr, std::string netmask)
{
    int ip4_octets = 4,
        ip4_octet_buffer = 8,
        ip_octet[4],
        netmask_octet[4],
        network_addr_buffer = 0;

    std::string binary_ip_octet[4],
                binary_netmask_octet[4],
                network_addr_octet[4];

    for (size_t i = 0; i < 4; i++)
    {
        ip_octet[i] = stoi( division_on_octet( ip4_addr, i ) );
        netmask_octet[i] = stoi( division_on_octet( netmask, i ) );

        binary_ip_octet[i] = std::to_string( dec_to_bin( ip_octet[i] ) );
        binary_netmask_octet[i] = std::to_string( dec_to_bin( netmask_octet[i] ) );
    }

    std::cout << ip4_addr << std::endl;
    std::cout << ip_octet[0] << std::endl;
    std::cout << binary_ip_octet[0] << std::endl;
    std::cout << netmask_octet[0] << std::endl;
    std::cout << binary_netmask_octet[0] << std::endl;


    // for (size_t i = 0; i < ip4_octets; i++)
    // {
    //     for (size_t y = 0; y < ip4_octet_buffer; y++)
    //     {
    //         network_addr_buffer = stoi(binary_ip_octet[y]) * stoi(binary_netmask_octet[y]);
    //     }
    // }

}
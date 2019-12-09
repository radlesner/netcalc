#include "check_ip.h"
#include "octet.h"
#include "convert_numbers.h"
#include "ip_operations.h"

void get_network_address(std::string bin_ip4_addr, std::string bin_netmask)
{
    if (bin_ip4_addr.length() != 32 || bin_netmask.length() != 32)
    {
        std::cout << "Addresses are too short" << std::endl;
        return;
    }
    else
    {
        int buffer,
            octet_indicator = 0,
            dec_network_octet_buffer;

        std::string bin_network_addr,
                    bin_network_octet[4],
                    bin_addr_buffer,
                    bin_netmask_buffer,
                    dec_network_octet[4];

        for (size_t i = 0; i < 32; i++)
        {
            bin_addr_buffer = bin_ip4_addr[i];
            bin_netmask_buffer = bin_netmask[i];

            buffer = std::stoi(bin_addr_buffer) * std::stoi(bin_netmask_buffer);

            bin_network_addr += std::to_string(buffer);
        }

        for (size_t i = 0; i < 32; i++)
        {
            bin_network_octet[octet_indicator] += bin_network_addr[i];

            if (i == 7 || i == 15 || i == 23)
            {
                octet_indicator++;
            }
        }

        for (size_t i = 0; i < 4; i++)
        {
            dec_network_octet_buffer = convertBinaryToDecimal(std::stoi( bin_network_octet[i] ));
            dec_network_octet[i] = std::to_string(dec_network_octet_buffer);
        }

        std::cout << "Network address: "
                  << dec_network_octet[0] << "."
                  << dec_network_octet[1] << "."
                  << dec_network_octet[2] << "."
                  << dec_network_octet[3] << std::endl;
    }
}
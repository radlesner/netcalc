#include "check_ip.h"
#include "octet.h"
#include "convert_numbers.h"
#include "ip_operations.h"

std::string get_network_address(std::string bin_ip4_addr, std::string bin_netmask)
{
    if (bin_ip4_addr.length() != 32 || bin_netmask.length() != 32)
    {
        std::cout << "get_network_address(): values are too short" << std::endl;
        return "";
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

        std::cout << "Network address:   "
                  << dec_network_octet[0] << "."
                  << dec_network_octet[1] << "."
                  << dec_network_octet[2] << "."
                  << dec_network_octet[3] << std::endl;

        return bin_network_addr;
    }
}

std::string get_broadcast_addr(std::string bin_network_addr, std::string bin_netmask)
{
    if (bin_network_addr.length() != 32 || bin_netmask.length() != 32)
    {
        std::cout << "get_broadcast_addr(): values are too short" << std::endl;
        return "";
    }
    else
    {
        std::string bin_netmask_invert = "11111111111111111111111111111111",
                    bin_netmask_inv_octet[4],
                    bin_network_octet[4],
                    bin_broadcast;

        int octet_indicator = 0,
            dec_netmask_inf_octet[4],
            dec_network_octet[4],
            dec_broadcast_addr[4];

        for (size_t i = 0; i < 32; i++)
        {
            if (bin_netmask[i] == '1')
            {
                bin_netmask_invert[i] = '0';
            }
        }

        for (size_t i = 0; i < 32; i++)
        {
            bin_netmask_inv_octet[octet_indicator] += bin_netmask_invert[i];
            bin_network_octet[octet_indicator] += bin_network_addr[i];

            if (i == 7 || i == 15 || i == 23)
            {
                octet_indicator++;
            }
        }

        for (size_t i = 0; i < 4; i++)
        {
            dec_netmask_inf_octet[i] = convertBinaryToDecimal(std::stoi(bin_netmask_inv_octet[i]));
            dec_network_octet[i] = convertBinaryToDecimal(std::stoi(bin_network_octet[i]));

            dec_broadcast_addr[i] = dec_netmask_inf_octet[i] + dec_network_octet[i];

            bin_broadcast += dec_to_bin(dec_broadcast_addr[i]);
        }

        std::cout << "Broadcast address: "
                  << dec_broadcast_addr[0] << "."
                  << dec_broadcast_addr[1] << "."
                  << dec_broadcast_addr[2] << "."
                  << dec_broadcast_addr[3] << std::endl;

        return bin_broadcast;
    }
}

void get_number_hosts(std::string bin_ip4_addr, std::string prefix)
{
    int ip_addr_length = bin_ip4_addr.length(),
        netmask_prefix = std::stoi(prefix),
        exponentiation_input = ip_addr_length - netmask_prefix,
        number_hosts;

    number_hosts = exponentiation(2, exponentiation_input);
    number_hosts -= 2;

    std::cout << "Number of hosts:   " << number_hosts << std::endl;
}

void get_first_last_host(std::string bin_network, std::string bin_broadcast)
{
    if (bin_network.length() != 32 || bin_broadcast.length() != 32)
    {
        std::cout << "get_first_last_host(): values are too short" << std::endl;
        return;
    }
    else
    {
        int octet_indicator = 0,
            first_host_octet[4],
            last_host_octet[4];

        std::string bin_network_octet[4],
                    bin_broadcast_octet[4];

        for (size_t i = 0; i < 32; i++)
        {
            bin_network_octet[octet_indicator] += bin_network[i];
            bin_broadcast_octet[octet_indicator] += bin_broadcast[i];

            if (i == 7 || i == 15 || i == 23)
            {
                octet_indicator++;
            }
        }

        for (size_t i = 0; i < 4; i++)
        {
            first_host_octet[i] = convertBinaryToDecimal(std::stoi(bin_network_octet[i]));
            last_host_octet[i] = convertBinaryToDecimal(std::stoi(bin_broadcast_octet[i]));

            if (i == 3)
            {
                first_host_octet[i] += 1;
                last_host_octet[i] -= 1;
            }
        }

        std::cout << "First host:        "
                  << first_host_octet[0] << "."
                  << first_host_octet[1] << "."
                  << first_host_octet[2] << "."
                  << first_host_octet[3] << std::endl;

        std::cout << "Last host:         "
                  << last_host_octet[0] << "."
                  << last_host_octet[1] << "."
                  << last_host_octet[2] << "."
                  << last_host_octet[3] << std::endl;
    }
}

long int exponentiation(long int base_of_power, int index)
{
    int result = 1;

    for (int i = 0; i < index; i++)
    {
        result *= base_of_power;
    }

    return result;
}
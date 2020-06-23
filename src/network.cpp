#include "headers/network.h"
#include "headers/convert_numbers.h"
#include "headers/octet.h"
#include "headers/output_messages.h"

void out_network_address(const std::string &bin_network_addr, const int &netmask_prefix)
{
    unsigned int dec_network_octet_buffer;
    std::vector<unsigned int> dec_network_octet;
    std::vector<std::string> bin_network_octet;
    std::string bin_addr_buffer, bin_netmask_buffer;

    bin_network_octet = get_bin_octets(bin_network_addr);

    for (size_t i = 0; i < 4; i++)
    {
        dec_network_octet_buffer = bin_to_dec(std::stoi(bin_network_octet[i]));
        dec_network_octet.push_back(dec_network_octet_buffer);
    }

    output_ip_address("  Network address: ", dec_network_octet, std::to_string(netmask_prefix));
}

std::string make_network_address(const std::string &bin_ip4_addr, const std::string &bin_netmask)
{
    unsigned int buffer, octet_indicator = 0, dec_network_octet_buffer;
    std::vector<unsigned int> dec_network_octet;
    std::vector<std::string> bin_network_octet;
    std::string bin_network_addr, bin_addr_buffer, bin_netmask_buffer;

    for (size_t i = 0; i < 32; i++)
    {
        bin_addr_buffer = bin_ip4_addr[i];
        bin_netmask_buffer = bin_netmask[i];
        buffer = std::stoi(bin_addr_buffer) * std::stoi(bin_netmask_buffer);
        bin_network_addr += std::to_string(buffer);

        if ((i == 7) || (i == 15) || (i == 23)) octet_indicator++;
    }

    // bin_network_octet = get_bin_octets(bin_network_addr);

    // for (size_t i = 0; i < 4; i++)
    // {
    //     dec_network_octet_buffer = bin_to_dec(std::stoi(bin_network_octet[i]));
    //     dec_network_octet.push_back(dec_network_octet_buffer);
    // }

    // output_ip_address("  Network address: ", dec_network_octet, std::to_string(netmask_prefix));
    return bin_network_addr;
}
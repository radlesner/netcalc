#include "headers/broadcast.h"
#include "headers/convert_numbers.h"
#include "headers/octet.h"
#include "headers/output_messages.h"

std::string get_broadcast_addr(const std::string &bin_network_addr, const std::string &bin_wildcard)
{
    std::vector<std::string> bin_network_octet = get_bin_octets(bin_network_addr),
                             bin_wildcard_octet = get_bin_octets(bin_wildcard);
    std::string bin_broadcast;
    std::vector<unsigned int> dec_netmask_inf_octet, dec_network_octet, dec_broadcast_addr;

    for (size_t i = 0; i < 4; i++)
    {
        dec_netmask_inf_octet.push_back(bin_to_dec(std::stoi(bin_wildcard_octet[i])));
        dec_network_octet.push_back(bin_to_dec(std::stoi(bin_network_octet[i])));
        dec_broadcast_addr.push_back(dec_netmask_inf_octet[i] + dec_network_octet[i]);
        bin_broadcast += dec_to_bin(dec_broadcast_addr[i]);
    }

    output_ip_address("Broadcast address: ", dec_broadcast_addr);
    return bin_broadcast;
}
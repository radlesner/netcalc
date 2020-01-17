#include "headers/netmask.h"
#include "headers/convert_numbers.h"
#include "headers/octet.h"
#include "headers/output_messages.h"

std::pair<std::string, std::string> make_netmask_and_wildcard(const int &prefix)
{
    std::vector<unsigned int> dec_netmask, dec_wildcard;
    std::string bin_netmask(32, '0'), bin_wildcard(32, '1'), netmask_buffer, wildcard_buffer;

    for (int i = 0; i < prefix; i++)
    {
        bin_netmask[i] = '1';
        bin_wildcard[i] = '0';
    }

    for (size_t i = 0; i < 32; i++)
    {
        netmask_buffer += bin_netmask[i];
        wildcard_buffer += bin_wildcard[i];

        if ((i == 7) || (i == 15) || (i == 23) || (i == 31))
        {
            dec_netmask.push_back(bin_to_dec(std::stoi(netmask_buffer)));
            netmask_buffer.clear();
            dec_wildcard.push_back(bin_to_dec(std::stoi(wildcard_buffer)));
            wildcard_buffer.clear();
        }
    }

    output_ip_address("Netmask:           ", dec_netmask);
    output_ip_address("Wildcard:          ", dec_wildcard);
    return {bin_netmask, bin_wildcard};
}

int make_prefix(const std::string &bin_netmask_input)
{
    int prefix = 0;

    for (size_t i = 0; i < 32; i++)
    {
        if (bin_netmask_input[i] == '1') prefix++;
    }

    return prefix;
}
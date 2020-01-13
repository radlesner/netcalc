#include "headers/netmask.h"
#include "headers/convert_numbers.h"
#include "headers/octet.h"
#include "headers/output_messages.h"

std::string make_netmask(const int &prefix)
{
    std::vector<unsigned int> dec_netmask;
    std::string bin_netmask(32, '0'), buffer;

    for (int i = 0; i < prefix; i++)
    {
        bin_netmask[i] = '1';
    }

    for (size_t i = 0; i < 32; i++)
    {
        buffer += bin_netmask[i];

        if (i == 7 || i == 15 || i == 23 || i == 31)
        {
            dec_netmask.push_back(bin_to_dec(std::stoi(buffer)));
            buffer.clear();
        }
    }

    output_ip_address("Netmask:           ", dec_netmask);
    return bin_netmask;
}

std::string make_wildcard_mask(const int &prefix)
{
    std::vector<unsigned int> dec_wildcard;
    std::string bin_wildcard(32, '1'), buffer;

    for (int i = 0; i < prefix; i++)
    {
        bin_wildcard[i] = '0';
    }

    for (size_t i = 0; i < 32; i++)
    {
        buffer += bin_wildcard[i];

        if (i == 7 || i == 15 || i == 23 || i == 31)
        {
            dec_wildcard.push_back(bin_to_dec(std::stoi(buffer)));
            buffer.clear();
        }
    }

    output_ip_address("Wildcard:          ", dec_wildcard);
    return bin_wildcard;
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
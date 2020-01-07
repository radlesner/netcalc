#include "headers/netmask.h"

#include "headers/convert_numbers.h"
#include "headers/octet.h"
#include "headers/output_messages.h"

std::string make_netmask(int prefix)
{
    std::string bin_netmask = "00000000000000000000000000000000", buffer[4];
    int octet_indicator = 0;
    std::vector<unsigned int> dec_netmask;

    for (int i = 0; i < prefix; i++)
    {
        bin_netmask[i] = '1';
    }

    for (size_t i = 0; i < 32; i++)
    {
        buffer[octet_indicator] += bin_netmask[i];

        if (i == 7 || i == 15 || i == 23)
        {
            octet_indicator++;
        }
    }

    for (size_t i = 0; i < 4; i++)
    {
        dec_netmask.push_back(convertBinaryToDecimal(std::stoi(buffer[i])));
    }

    output_ip_address("Netmask:           ", dec_netmask);
    return bin_netmask;
}

int make_prefix(std::string bin_netmask_input)
{
    int prefix = 0;

    for (size_t i = 0; i < 32; i++)
    {
        if (bin_netmask_input[i] == '1')
        {
            prefix++;
        }
    }

    return prefix;
}
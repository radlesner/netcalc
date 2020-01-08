#include "headers/netmask.h"

#include "headers/convert_numbers.h"
#include "headers/octet.h"
#include "headers/output_messages.h"

std::string make_netmask(int prefix)
{
    std::vector<unsigned int> dec_netmask;
    std::string
        bin_netmask = "00000000000000000000000000000000",
        buffer;

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

int make_prefix(std::string bin_netmask_input)
{
    int prefix = 0;

    for (size_t i = 0; i < 32; i++)
    {
        if (bin_netmask_input[i] == '1')
            prefix++;
    }

    return prefix;
}
#include "headers/netmask.h"
#include "headers/octet.h"
#include "headers/convert_numbers.h"

std::string make_netmask(std::string prefix)
{
    std::string
        bin_netmask,
        bin_netmask_octet[4],
        dec_netmask;

    int octet_indicator = 0,
        int_netmask[4];

    for (int i = 0; i < std::stoi(prefix); i++)
    {
        bin_netmask += "1";
    }

    do
    {
        bin_netmask += "0";
    } while (bin_netmask.length() != 32);



    for (size_t i = 0; i < 32; i++)
    {
        bin_netmask_octet[octet_indicator] += bin_netmask[i];

        if (i == 7 || i == 15 || i == 23)
        {
            octet_indicator++;
        }
    }

    for (size_t i = 0; i < 4; i++)
    {
        int_netmask[i] = convertBinaryToDecimal(std::stoi(bin_netmask_octet[i]));
    }

    std::cout
        << "Netmask:           "
        << int_netmask[0] << "."
        << int_netmask[1] << "."
        << int_netmask[2] << "."
        << int_netmask[3] << std::endl;

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
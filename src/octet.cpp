#include "headers/octet.h"

// -------------------------------------------------------------------------------------
std::vector<std::string> get_dec_octet(const std::string &ip4_addr)
{
    std::vector<std::string> ip_octet;
    std::string buffer;

    for (auto i = ip4_addr.begin(); i <= ip4_addr.end(); i++)
    {
        if ((*i == '.') || (i == ip4_addr.end()))
        {
            ip_octet.push_back(buffer);
            buffer.clear();
            i++;
        }

        buffer += *i;
    }

    return ip_octet;
}

// -------------------------------------------------------------------------------------
std::vector<std::string> get_bin_octets(const std::string &bin_addr)
{
    std::vector<std::string> bin_octet;
    std::string buffer;

    for (size_t i = 0; i < bin_addr.length(); i++)
    {
        buffer += bin_addr[i];

        if ((i == 7) || (i == 15) || (i == 23) || (i == 31))
        {
            bin_octet.push_back(buffer);
            buffer.clear();
        }
    }

    return bin_octet;
}
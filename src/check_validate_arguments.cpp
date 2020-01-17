#include "headers/check_validate_arguments.h"

bool is_valid_ip(const std::string &ipStr)
{
    int ip3, ip2, ip1, ip0;
    if (4 != sscanf(ipStr.c_str(), "%d.%d.%d.%d", &ip3, &ip2, &ip1, &ip0))
    {
        return false;
    }
    for (auto p : {&ip3, &ip2, &ip1, &ip0})
    {
        if ((*p > 255) || (*p < 0))
        {
            return false;
        }
    }
    return true;
}

bool is_valid_netmask_prefix(const std::string &str_prefix)
{
    for (size_t i = 0; i < str_prefix.length(); i++)
    {
        if (!isdigit(str_prefix[i])) return false;
    }

    if ((std::stoi(str_prefix) < 1) || (std::stoi(str_prefix) > 31)) return false;

    return true;
}
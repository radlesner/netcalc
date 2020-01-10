#include "headers/check_prefix.h"

bool is_valid_netmask_prefix(char* netmask_prefix)
{
    std::string str_prefix = netmask_prefix;
    for (size_t i = 0; i < str_prefix.length(); i++)
    {
        if (!isdigit(str_prefix[i])) return false;
    }

    if (str_prefix.length() >= 2)
    {
        if (std::stoi(str_prefix) < 0 || std::stoi(str_prefix) > 31) return false;
    }

    return true;
}
#include "headers/check_prefix.h"

bool is_valid_netmask_prefix(int netmask_prefix)
{
    std::string netmask_string_value = std::to_string(netmask_prefix);

    if (netmask_string_value.length() == 1)
    {
        if (static_cast<int>(netmask_string_value[0]) >= 48 && static_cast<int>(netmask_string_value[0]) <= 57)
        {
            if (std::stoi(netmask_string_value) < 0 || std::stoi(netmask_string_value) > 31)
                return false;
        }
        else
            return false;
    }

    if (netmask_string_value.length() == 2)
    {
        if (static_cast<int>(netmask_string_value[1]) >= 48 && static_cast<int>(netmask_string_value[1]) <= 57)
        {
            if (std::stoi(netmask_string_value) < 0 || std::stoi(netmask_string_value) > 31)
                return false;
        }
        else
            return false;
    }
    else
        return false;

    return true;
}
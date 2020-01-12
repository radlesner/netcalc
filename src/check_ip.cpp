#include "headers/check_ip.h"

bool valid_digit(char *ip_str)
{
    while (*ip_str)
    {
        if (*ip_str >= '0' && *ip_str <= '9')
            ++ip_str;
        else
            return false;
    }
    return true;
}

bool is_valid_ip(std::string ip_input)
{
    int num, dots = 0;
    char *ptr, *buffer = const_cast<char *>(ip_input.c_str());

    if (buffer == NULL) return false;
    ptr = strtok(buffer, DELIM);

    if (ptr == NULL) return false;

    while (ptr)
    {
        if (!valid_digit(ptr)) return false;

        num = std::stoi(ptr);

        if (num >= 0 && num <= 255)
        {
            ptr = strtok(NULL, DELIM);
            if (ptr != NULL) ++dots;
        }
        else
            return false;
    }

    if (dots != 3) return false;
    return true;
}
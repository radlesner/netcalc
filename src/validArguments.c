#include "headers/validArguments.h"

// -------------------------------------------------------------
bool isIPValid(const char *ipAddress)
{
    int ipArray[4];
    if (4 != sscanf(ipAddress, "%d.%d.%d.%d", &ipArray[0], &ipArray[1], &ipArray[2], &ipArray[3]))
    {
        return false;
    }

    for (int i = 0; i < 4; i++)
    {
        if ((ipArray[i] > 255) || (ipArray[i] < 0))
        {
            return false;
        }
    }

    return true;
}

// -------------------------------------------------------------
bool isMaskPrefixValid(const char *maskPrefixStr)
{
    int i = 0;
    int intPrefix;

    if (maskPrefixStr[i] == '-')
    {
        i++;
    }

    while (maskPrefixStr[i] != '\0')
    {
        if (!isdigit(maskPrefixStr[i]))
        {
            return false;
        }

        i++;
    }

    intPrefix = atoi(maskPrefixStr);
    if (intPrefix < 1 || intPrefix > 31)
    {
        return false;
    }

    return true;
}

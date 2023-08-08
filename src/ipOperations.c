#include "headers/ipOperations.h"

// -------------------------------------------------------------
void getWildAddr(unsigned int ipWildTab[], unsigned int ipMaskTab[])
{
    for (int i = 0; i < 4; i++)
    {
        ipWildTab[i] = ipMaskTab[i] ^ 255;
    }
}

// -------------------------------------------------------------
void getNetworkAddr(unsigned int ipNetAddrTab[], unsigned int ipAddrTab[], unsigned int ipMaskTab[])
{
    for (int i = 0; i < 4; i++)
    {
        ipNetAddrTab[i] = ipAddrTab[i] & ipMaskTab[i];
    }
}

// -------------------------------------------------------------
void getBroadAddr(unsigned int ipBroadAddrTab[], unsigned int ipNetAddrTab[], unsigned int ipMaskTab[])
{
    for (int i = 0; i < 4; i++)
    {
        ipBroadAddrTab[i] = ipNetAddrTab[i] | (~ipMaskTab[i] & 0xFF);
    }
}

// -------------------------------------------------------------
void getFirstLastHost(unsigned int ipFirstHost[], unsigned int ipLastHost[], unsigned int ipNetAddrTab[], unsigned int ipBroadAddrTab[])
{
    for (int i = 0; i < 4; i++)
    {
        ipFirstHost[i] += ipNetAddrTab[i];
        ipLastHost[i] += ipBroadAddrTab[i];

        if (i == 3)
        {
            ipFirstHost[i] += 1;
            ipLastHost[i] -= 1;
        }
    }
}

// -------------------------------------------------------------
unsigned int getHostNumber(unsigned int rawMaskPrefix)
{
    unsigned int numHost;

    numHost = (1 << (32 - rawMaskPrefix)) - 2;
    return numHost;
}

// -------------------------------------------------------------
int ipcmp(unsigned int ipTab[], int oct1, int oct2, int oct3, int oct4)
{
    int matchingOctets           = 0;
    int boolResult               = 1;
    unsigned int compareIpTab[4] = {oct1, oct2, oct3, oct4};

    for (int i = 0; IP4_MAX_OCTET < 4; i++)
    {
        if (ipTab[i] == compareIpTab[i])
        {
            matchingOctets++;
        }
    }

    if (matchingOctets == 4)
        boolResult = 1; // TRUE
    else
        boolResult = 0; // FALSE

    return boolResult;
}

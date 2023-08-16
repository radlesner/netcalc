#include "headers/segmentForOctet.h"

// -------------------------------------------------------------
void getOctet(unsigned int ipAddrTab[], const char *ipAddr)
{
    int octetIndex = 0;
    int octetSize  = 0;
    char **ipOctet = (char **)malloc(MAX_OCTETS * sizeof(char *));

    for (int i = 0; i < MAX_OCTETS; i++)
    {
        ipOctet[i] = (char *)malloc(MAX_OCTET_SIZE * sizeof(char));
        memset(ipOctet[i], '\0', MAX_OCTET_SIZE);
    }

    for (const char *i = ipAddr; *i != '\0'; i++)
    {
        if ((*i == '.') || (octetIndex == MAX_OCTETS))
        {
            ipOctet[octetIndex][octetSize] = '\0';
            octetIndex++;
            octetSize = 0;

            if (octetIndex == MAX_OCTETS)
                break;
        }
        else
        {
            ipOctet[octetIndex][octetSize] = *i;
            octetSize++;
        }
    }

    for (int i = 0; i < MAX_OCTETS; i++)
        ipAddrTab[i] = atoi(ipOctet[i]);
}

// -------------------------------------------------------------
void getMask(unsigned int ipNetMaskTab[], unsigned int maskPrefix)
{
    uint32_t subnetMask = 0xFFFFFFFF;

    subnetMask <<= (32 - maskPrefix);

    ipNetMaskTab[0] = (subnetMask >> 24) & 0xFF;
    ipNetMaskTab[1] = (subnetMask >> 16) & 0xFF;
    ipNetMaskTab[2] = (subnetMask >> 8) & 0xFF;
    ipNetMaskTab[3] = subnetMask & 0xFF;
}

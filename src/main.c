#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Include files
#include "gtk/headers/gtkMain.h"
#include "headers/ipOperations.h"
#include "headers/netInterfaces.h"
#include "headers/outputs.h"
#include "headers/segmentForOctet.h"
#include "headers/validArguments.h"

// --------------------------------------------------- MAIN ---------------------------------------------------
int main(int argc, char *argv[])
{
    unsigned int ipAddr[4] = {0, 0, 0, 0};
    unsigned int ipMask[4] = {0, 0, 0, 0};

    if (argc == 1)
    {
        gtkWindowInit(argc, argv);
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        if ((!strcmp(argv[1], "-i")) || (!strcmp(argv[1], "--inteface")))
        {
            if (argc >= 3)
            {
                getInterfaceInfo(argv[2], ipAddr, ipMask);
                int maskPrefix = maskToPrefix(ipMask);
                mainOutput(ipAddr, maskPrefix);
            }
            else
            {
                showInterfaces();
            }

            break;
        }
        else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--calculator") == 0)
        {
            if (argc >= 4)
            {
                if (isIPValid(argv[2]) && isMaskPrefixValid(argv[3]))
                {
                    getOctet(ipAddr, argv[2]);
                    mainOutput(ipAddr, atoi(argv[3]));
                }
                else
                {
                    printf("Not valid IP address or mask prefix\n");
                }
            }
            else
            {
                printf("Usage: netcalc [ip_v4_address] [prefix_netmask] or -h option\n");
            }

            break;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            helpOutput();
            break;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            printf("netcalc, version %s\n", VERSION_PROGRAM);
            break;
        }
        else
        {
            printf("Unknown option: %s\n", argv[i]);
        }
    }

    return 0;
}

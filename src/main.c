#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Include files
#include "headers/ipOperations.h"
#include "headers/netInterfaces.h"
#include "headers/outputs.h"
#include "headers/segmentForOctet.h"
#include "headers/validArguments.h"

#define VERSION_PROGRAM "3.2"

// --------------------------------------------------- MAIN ---------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Provide the CLI argument\n");
        printf("Usage: netcalc [ip_v4_address] [prefix_netmask] or -h option\n");
    }

    for (int i = 1; i < argc; i++)
    {
        if ((!strcmp(argv[1], "-i")) || (!strcmp(argv[1], "--inteface")))
        {
            if (argc >= 2)
            {
                showInterfaces();
                return 0;
            }
            else
            {
                getInterfaceInfo(argv[2]);
                return 0;
            }
        }
        else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--calculator") == 0)
        {
            if (argc >= 4)
            {
                if (isIPValid(argv[2]) && isMaskValid(argv[3]))
                {
                    mainOutput(argv[2], atoi(argv[3]));
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

            return 0;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            helpOutput();
            return 0;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            printf("netcalc, version %s\n", VERSION_PROGRAM);
            return 0;
        }
        else
        {
            printf("Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    return 0;
}
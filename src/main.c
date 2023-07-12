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

#define VERSION_PROGRAM  "3.2"
#define ARG_IP_ADDR_SIZE 15
#define ARG_PREFIX_SIZE  2

// --------------------------------------------------- MAIN ---------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        if ((!strcmp(argv[1], "-i")) || (!strcmp(argv[1], "--inteface")))
        {
            getInterfaceInfo(argv[2]);
            return 0;
        }

        if (!isIPValid(argv[1]) && !isMaskValid(argv[2]))
        {
            printf("Bad arguments!\n");
            printf("Usage: netcalc [ip_v4_address] [prefix_netmask] or -h option\n");
            return 0;
        }

        mainOutput(argv[1], atoi(argv[2]));
    }
    else if (argc > 1)
    {
        if ((!strcmp(argv[1], "-h")) || (!strcmp(argv[1], "--help")))
        {
            helpOutput();
        }
        else if ((!strcmp(argv[1], "-i")) || (!strcmp(argv[1], "--inteface")))
        {
            showInterfaces();
        }
        else if ((!strcmp(argv[1], "-v")) || (!strcmp(argv[1], "--version")))
        {
            printf("netcalc, version %s\n", VERSION_PROGRAM);
        }
    }

    return 0;
}
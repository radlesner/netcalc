#include "headers/get_network_addresses.h"
#include "headers/output.h"

int main(int argc, char *argv[])
{
	if(argc > 2)
	{
        if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--inteface"))
        {
            get_network_inteface(argv[2]);
        }
        else
        {
            get_network_argument(argv[1], argv[2]);
        }
	}
    else if (argc > 1)
    {
        if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))
        {
            version_program();
        }
        else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
        {
            help_panel();
        }
        else if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--inteface"))
        {
            show_interfaces();
        }
        else
        {
            error_message_argument(argv[1]);
        }
    }
    else
    {
        usage_message();
    }

    return 0;
}
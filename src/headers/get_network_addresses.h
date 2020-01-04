#include <iostream>
#include <ifaddrs.h>
#include <arpa/inet.h>

#include "octet.h"
#include "convert_numbers.h"
#include "ip_operations.h"
#include "netmask.h"
#include "output.h"
#include "check_ip.h"
#include "check_prefix.h"

void        get_network_argument    (char *ip_argument, char *prefix_argument);
void        get_network_inteface    (char *interface_name);
void        show_interfaces         ();
std::string add_color_string        (std::string text_input);

#include <arpa/inet.h>
#include <ifaddrs.h>

#include <iostream>

#include "check_ip.h"
#include "check_prefix.h"
#include "convert_numbers.h"
#include "ip_operations.h"
#include "netmask.h"
#include "octet.h"
#include "output_messages.h"

void        get_network_argument(char *ip_argument, char *prefix_argument);
void        get_network_inteface(char *interface_name);
void        show_interfaces();
std::string add_valid_color(std::string text_input);
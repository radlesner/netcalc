#include <arpa/inet.h>
#include <ifaddrs.h>
#include <iostream>

void get_network_argument(const std::string &ip_argument, const std::string &prefix_argument);
void get_network_inteface(const std::string &interface_name);
void show_interfaces();
std::string add_valid_color(std::string text_input);
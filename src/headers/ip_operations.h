#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

std::string make_bin_address(const std::string &bin_input);
std::string get_network_address(const std::string &bin_ip4_addr, const std::string &bin_netmask);
std::string get_broadcast_addr(const std::string &bin_network_addr, const std::string &bin_wildcard);
void get_number_hosts(const std::string &bin_ip4_addr, const int &prefix);
void get_first_last_host(const std::string &bin_ip4_addr, const std::string &bin_network);
long int exponentiation(const long int &base_of_power, const int &index);
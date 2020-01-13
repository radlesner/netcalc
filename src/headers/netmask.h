#include <iostream>
#include <string>
#include <utility>

std::pair<std::string, std::string> make_netmask_and_wildcard(const int &prefix);
int make_prefix(const std::string &bin_netmask_input);
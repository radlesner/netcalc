#include <iostream>
#include <vector>

#define VERSION_PROGRAM "3.2"

void version_program();
void output_ip_address(const std::string &label, std::vector<unsigned int> input, const std::string &extra_label = "");
void help_panel();
void usage_message();
void error_message();
void error_message_argument(const std::string &argument_input);
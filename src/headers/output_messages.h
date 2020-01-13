#include <iostream>
#include <vector>

#define VERSION_PROGRAM "3.0"

void version_program();
void output_ip_address(const std::string &label, std::vector<unsigned int> input);
void help_panel();
void usage_message();
void error_message();
void error_message_argument(char *argument_input);
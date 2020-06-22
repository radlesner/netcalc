#include "headers/ip_operations.h"
#include "headers/convert_numbers.h"
#include "headers/octet.h"
#include "headers/output_messages.h"

std::string group_long_number(int input_number)
{
    std::string string_input = std::to_string(input_number), output;
    int buffer = 0;

    for (auto i = string_input.rbegin(); i < string_input.rend(); ++i)
    {
        buffer++;
        output += *i;
        if (buffer == 3)
        {
            output += ' ';
            buffer = 0;
        }
    }
    reverse(output.begin(), output.end());
    if (output[0] == ' ') output.erase(0, 1);

    return output;
}

void exponentiation(const long int &base_of_power, int &index)
{
    int result = 1;
    for (int i = 0; i < index; i++)
    {
        result *= base_of_power;
    }
    index = result;
}

std::string make_bin_address(const std::string &dec_input)
{
    std::vector<std::string> string_octet_remainder = get_dec_octet(dec_input);
    std::string bin_ip_address;
    std::vector<int> ip_octet;
    int octet_buffer;

    for (int i = 0; i < 4; i++)
    {
        octet_buffer = std::stoi(string_octet_remainder[i]);
        ip_octet.push_back(octet_buffer);
        bin_ip_address += dec_to_bin(ip_octet[i]);
    }

    return bin_ip_address;
}

void get_number_hosts(const std::string &bin_ip4_addr, const int &prefix)
{
    int number_hosts = bin_ip4_addr.length() - prefix;
    std::string output;

    exponentiation(2, number_hosts);
    number_hosts -= 2;
    output = group_long_number(number_hosts);

    std::cout << "  Number of hosts: " << output << std::endl;
}

void get_first_last_host(const std::string &bin_network, const std::string &bin_broadcast)
{
    std::vector<unsigned int> first_host_octet, last_host_octet;
    std::vector<std::string> bin_network_octet = get_bin_octets(bin_network),
                             bin_broadcast_octet = get_bin_octets(bin_broadcast);

    for (size_t i = 0; i < 4; i++)
    {
        first_host_octet.push_back(bin_to_dec(std::stoi(bin_network_octet[i])));
        last_host_octet.push_back(bin_to_dec(std::stoi(bin_broadcast_octet[i])));

        if (i == 3)
        {
            first_host_octet[i] += 1;
            last_host_octet[i] -= 1;
        }
    }

    output_ip_address("       First host: ", first_host_octet);
    output_ip_address("        Last host: ", last_host_octet);
}
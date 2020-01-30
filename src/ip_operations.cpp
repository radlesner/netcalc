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

std::string get_network_address(const std::string &bin_ip4_addr, const std::string &bin_netmask)
{
    unsigned int buffer, octet_indicator = 0, dec_network_octet_buffer;
    std::vector<unsigned int> dec_network_octet;
    std::vector<std::string> bin_network_octet;
    std::string bin_network_addr, bin_addr_buffer, bin_netmask_buffer;

    for (size_t i = 0; i < 32; i++)
    {
        bin_addr_buffer = bin_ip4_addr[i];
        bin_netmask_buffer = bin_netmask[i];
        buffer = std::stoi(bin_addr_buffer) * std::stoi(bin_netmask_buffer);
        bin_network_addr += std::to_string(buffer);

        if ((i == 7) || (i == 15) || (i == 23)) octet_indicator++;
    }

    bin_network_octet = get_bin_octets(bin_network_addr);

    for (size_t i = 0; i < 4; i++)
    {
        dec_network_octet_buffer = bin_to_dec(std::stoi(bin_network_octet[i]));
        dec_network_octet.push_back(dec_network_octet_buffer);
    }

    output_ip_address("Network address:   ", dec_network_octet);
    return bin_network_addr;
}

std::string get_broadcast_addr(const std::string &bin_network_addr, const std::string &bin_wildcard)
{
    std::vector<std::string> bin_network_octet = get_bin_octets(bin_network_addr),
                             bin_wildcard_octet = get_bin_octets(bin_wildcard);
    std::string bin_broadcast;
    std::vector<unsigned int> dec_netmask_inf_octet, dec_network_octet, dec_broadcast_addr;

    for (size_t i = 0; i < 4; i++)
    {
        dec_netmask_inf_octet.push_back(bin_to_dec(std::stoi(bin_wildcard_octet[i])));
        dec_network_octet.push_back(bin_to_dec(std::stoi(bin_network_octet[i])));
        dec_broadcast_addr.push_back(dec_netmask_inf_octet[i] + dec_network_octet[i]);
        bin_broadcast += dec_to_bin(dec_broadcast_addr[i]);
    }

    output_ip_address("Broadcast address: ", dec_broadcast_addr);
    return bin_broadcast;
}

void get_number_hosts(const std::string &bin_ip4_addr, const int &prefix)
{
    int number_hosts = bin_ip4_addr.length() - prefix;
    std::string output;

    exponentiation(2, number_hosts);
    number_hosts -= 2;
    output = group_long_number(number_hosts);

    std::cout << "Number of hosts:   " << output << std::endl;
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

    output_ip_address("First host:        ", first_host_octet);
    output_ip_address("Last host:         ", last_host_octet);
}
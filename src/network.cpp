#include "network.h"
#include "ip.h"
#include <iostream>
#include <cmath>
#include <bitset>

Network::Network(IP ip_address, IP subnet_mask)
    : ip_address(ip_address), subnet_mask(subnet_mask)
{
}

IP Network::get_network_id()
{
  // network_id = subnet_mask & ip_address
  IP network_id = subnet_mask.get_ip() & ip_address.get_ip();

  return network_id;
}

IP Network::get_broadcast_id()
{
  // broadcast_id = network_id | inverted subnet_mask
  IP broadcast_id = this->get_network_id().get_ip() | (~subnet_mask.get_ip());

  return broadcast_id;
}

IP Network::get_first_ip()
{
  IP first_ip = this->get_network_id().get_ip() + 0b1;

  return first_ip;
}

IP Network::get_last_ip()
{
  IP last_ip = this->get_broadcast_id().get_ip() - 0b1;

  return last_ip;
}

int Network::get_total_hosts()
{
  return (int)~subnet_mask.get_ip() + 1;
}

int Network::get_usable_hosts()
{
  return (int)~subnet_mask.get_ip() - 1;
}

void Network::print_subnets(int subnet_bits)
{
  int number_of_hosts = (~subnet_mask.get_ip() >> subnet_bits) + 1;

  IP subnet_id = this->get_network_id();
  int i = 1;

  std::cout << "\nsubnet\tsubnet id\tusable hosts\t\t\tbroadcast id\n";
  std::cout << "---------------------------------------------------------------------\n";
  while (i <= pow(2, subnet_bits))
  {
    std::cout << i << "\t";
    subnet_id.print_in_decimal();
    std::cout << "\t";

    IP::print_in_decimal(subnet_id.get_ip() + 1);
    std::cout << " - ";

    IP::print_in_decimal(subnet_id.get_ip() + number_of_hosts - 2);
    std::cout << "\t";

    IP::print_in_decimal(subnet_id.get_ip() + number_of_hosts - 1);

    std::cout << "\n";

    subnet_id.set_ip(subnet_id.get_ip() + number_of_hosts);
    i++;
  }

  std::cout << "\n";

  std::cout << "Total hosts per subnet: " << number_of_hosts << "\n";
}

int Network::get_prefix_length()
{
  uint32_t mask = subnet_mask.get_ip();
  int count = 0;

  while (mask)
  {
    count += mask & 1;
    mask >>= 1;
  }
  return count;
}

bool Network::is_ip_in_network(IP ip)
{
  return (ip.get_ip() & subnet_mask.get_ip()) == this->get_network_id().get_ip();
}
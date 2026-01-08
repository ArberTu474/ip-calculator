#include "network.h"
#include "ip.h"
#include <iostream>
#include <vector>

Network::Network(IP ip_address, IP subnet_mask)
    : ip_address(ip_address), subnet_mask(subnet_mask)
{
}

IP Network::get_ip() const
{
  return this->ip_address;
}

IP Network::get_subnet_mask() const
{
  return this->subnet_mask;
}

IP Network::get_wildcard_mask() const
{
  return ~subnet_mask.get_ip();
}

IP Network::get_network_id() const
{
  // network_id = subnet_mask & ip_address
  return subnet_mask.get_ip() & ip_address.get_ip();
}

IP Network::get_broadcast_id() const
{
  // broadcast_id = network_id | inverted subnet_mask
  return this->get_network_id().get_ip() | (~subnet_mask.get_ip());
}

IP Network::get_first_ip() const
{
  // first ip comes after the network id
  return this->get_network_id().get_ip() + 1;
}

IP Network::get_last_ip() const
{
  // the last ip comes before the broadcast id
  return this->get_broadcast_id().get_ip() - 1;
}

int Network::get_total_hosts() const
{
  // Example
  // subnet mask:           11111111.11111111.11111111.00000000
  // inverted subnet mask:  00000000.00000000.00000000.11111111
  // If we add 1 to the inverted subnet mask we get the total number of hosts
  return (int)~subnet_mask.get_ip() + 1;
}

int Network::get_usable_hosts() const
{
  // In the total hosts rage 2 ips are reserved for network id and broadcast id
  return this->get_total_hosts() - 2;
}

void Network::print_subnets(int subnet_bits)
{
  int new_prefix = this->get_prefix_length() + subnet_bits;

  // To get a subnet mask with a specific prefix we get a number we 32 ones and shift it a ceratin amout of bits
  IP new_subnet_mask = ~uint32_t(0) << (32 - new_prefix);

  // We shift the number 1 as many times as the number of subnet_bits
  // This way we don't need to use the pow() function

  // Exampls
  // subnet bits: 3
  // shift the bits to the left by 3 positions
  // we end up with: 00001000 = 8
  int number_of_subnets = (1 << subnet_bits);

  // We invert the subnet mask and add 1 to get the total number of hosts
  // We remove (shift to the right) the subnet bits and the rest of the bits give the number of hosts
  int number_of_hosts_per_subnet = (~new_subnet_mask.get_ip()) + 1;

  // This vector is going to hold each subnet in the form of a Network
  std::vector<Network> subnets;

  // first subnet id is equal to the network id
  IP subnet_id = this->get_network_id();

  for (int i = 0; i < number_of_subnets; i++)
  {
    subnets.push_back(Network(subnet_id, new_subnet_mask));

    // We add the subnet block size to the current subnet id to get the next one subnet id
    subnet_id.set_ip(subnet_id.get_ip() + number_of_hosts_per_subnet);
  }

  int i = 1;

  std::cout << "\nsubnet\tsubnet id\tusable hosts\t\t\tbroadcast id\n";
  std::cout << "---------------------------------------------------------------------\n";
  for (auto &&subnet : subnets)
  {
    std::cout << i << "\t"
              << subnet.get_network_id() << "\t"    // subnet id
              << subnet.get_first_ip() << " - "     // first usable host
              << subnet.get_last_ip() << "\t"       // last usable host
              << subnet.get_broadcast_id() << "\n"; // broadcast id
    i++;
  }

  std::cout << "\n";
  std::cout << "Total subnets:\t\t\t" << number_of_subnets << "\n";
  std::cout << "Total hosts per subnet:'t\t" << number_of_hosts_per_subnet << "\n";
  std::cout << "Total usable hosts per subnet:\t" << number_of_hosts_per_subnet - 2 << "\n";
  std::cout << "Total usable hosts:\t\t" << (number_of_hosts_per_subnet - 2) * number_of_subnets << "\n";
}

int Network::get_prefix_length() const
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

bool Network::is_ip_in_network(IP ip) const
{
  // For in ip to be in a specific network it should:
  // ip & subnet_mask == network_id

  // Example
  // ip:          192.168.1.40
  // subnet_mask: 255.255.255.0
  // network_id:  192.168.1.40

  // ip:                11000000.10101000.00000001.00101000
  // subnet_mask:       11111111.11111111.11111111.00000000
  // ip & subnet_mask:  11000000.10101000.00000001.00000000
  // network_id:        11000000.10101000.00000001.00000000
  // in this case ip & subnet_mask is equal to the network id, so the first ip is in the network

  // the subnet mask helps us grab the part of the network id and ignore the host part
  return (ip.get_ip() & subnet_mask.get_ip()) == this->get_network_id().get_ip();
}
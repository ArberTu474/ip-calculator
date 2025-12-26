#include <iostream>
#include "ip.h"
#include "network.h"

int main()
{
  IP ip1(192, 168, 1, 10);
  IP sm(255, 255, 255, 0);

  ip1.print_in_decimal();
  std::cout << "\n";
  ip1.print_in_binary();

  Network n(ip1, sm);

  std::cout << "\nNetwork Id: ";
  n.get_network_id().print_in_decimal();
  std::cout << "\n";
  n.get_network_id().print_in_binary();
  std::cout << "\nBroadcast Id: ";
  n.get_broadcast_id().print_in_decimal();

  std::cout << "\nFirst Ip: ";
  n.get_first_ip().print_in_decimal();
  std::cout << "\nLast Ip: ";
  n.get_last_ip().print_in_decimal();

  std::cout << "\nTotal hosts: " << n.get_total_hosts() << "\n";
  std::cout << "Total usable hosts: " << n.get_usable_hosts() << "\n";

  n.print_subnets(3);

  std::cout << "Ip class: " << ip1.get_ip_class() << "\n";

  std::cout << "is ip in network: (192.168.1.40) " << n.is_ip_in_network(IP(255, 168, 3, 8)) << "\n";
  std::cout << "Prefix length: " << n.get_prefix_length() << "\n";

  return 0;
}
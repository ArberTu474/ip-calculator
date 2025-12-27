#include <iostream>
#include "ip.h"
#include "network.h"

int main()
{
  IP ip1(192, 168, 1, 10);
  IP ip2(192, 168, 2, 20);
  IP sm(255, 255, 255, 0);

  Network n(ip1, sm);

  // Network ID:     192.168.1.0
  // Broadcast:      192.168.1.255
  // Subnet Mask:    255.255.255.0 (/24)
  // First Host:     192.168.1.1
  // Last Host:      192.168.1.254
  // Total Host:     256
  // Usable Hosts:   254
  // Network Class:  C

  std::cout << "IP address:\t" << ip1 << "\n";

  std::cout << "Network ID:\t" << n.get_network_id() << "\n";

  std::cout << "Broadcast:\t" << n.get_broadcast_id() << "\n";

  std::cout << "Subnet Mask:\t" << n.get_subnet_mask() << " (/" << n.get_prefix_length() << ")\n";

  std::cout << "Wildcard Mask:\t" << n.get_wildcard_mask() << "\n";

  std::cout << "First Host:\t" << n.get_first_ip() << "\n";

  std::cout << "Last Host:\t" << n.get_last_ip() << "\n";

  std::cout << "Total Hosts:\t" << n.get_total_hosts() << "\n";

  std::cout << "Usable Hosts:\t" << n.get_usable_hosts() << "\n";

  std::cout << "Network Class:\t" << n.get_ip().get_ip_class() << "\n";

  std::cout << "Is " << ip2 << " in the network?\t" << (n.is_ip_in_network(ip2) ? "Yes" : "No") << "\n";

  n.print_subnets(2);

  return 0;
}
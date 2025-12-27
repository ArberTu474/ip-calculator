#ifndef NETWORK_H
#define NETWORK_H

#include "ip.h"

class Network
{
private:
    IP ip_address;
    IP subnet_mask;

public:
    // Constructor
    Network(IP ip_address, IP subnet_mask);

    // Getters
    IP get_ip();
    IP get_subnet_mask();
    IP get_wildcard_mask();

    IP get_network_id();
    IP get_broadcast_id();
    IP get_first_ip();
    IP get_last_ip();

    int get_total_hosts();
    int get_usable_hosts();
    int get_prefix_length();

    void print_subnets(int subnet_bits);

    // check if a ip belongs to a network
    bool is_ip_in_network(IP ip);
};

#endif

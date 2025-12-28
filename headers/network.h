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
    IP get_ip() const;
    IP get_subnet_mask() const;
    IP get_wildcard_mask() const;

    IP get_network_id() const;
    IP get_broadcast_id() const;
    IP get_first_ip() const;
    IP get_last_ip() const;

    int get_total_hosts() const;
    int get_usable_hosts() const; 
    int get_prefix_length() const;

    void print_subnets(int subnet_bits);

    // check if a ip belongs to a network
    bool is_ip_in_network(IP ip) const;
};

#endif

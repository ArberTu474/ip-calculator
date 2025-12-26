#ifndef IP_H
#define IP_H

#include <cstdint>

class IP
{
private:
  uint32_t ip;
  uint8_t ip_octets[4];

public:
  // Constructor
  IP(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4);
  IP(uint32_t full_ip);

  /// @brief Prints the ip address in decimal form. eg. 192.168.0.1
  void print_in_decimal() const;

  /// @brief Prints the ip address in binary form. eg. 11000000.10101000.00000001.00000001
  void print_in_binary() const;

  /// @brief Prints the ip address in decimal form. eg. 192.168.0.1
  static void print_in_decimal(uint32_t ip);

  /// @brief Prints the ip address in binary form. eg. 11000000.10101000.00000001.00000001
  static void print_in_binary(uint32_t ip);

  // Getters
  uint32_t get_ip();

  uint8_t get_octet(int octet);

  char get_ip_class();

  // Setters
  void set_ip(uint32_t ip);

};

#endif
#ifndef IP_H
#define IP_H

#include <cstdint>
#include <ostream>

class IP
{
private:
  uint32_t ip;

public:
  // Constructor
  IP(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4);
  IP(uint32_t full_ip);

  void print_in_decimal() const;
  void print_in_binary() const;

  static void print_in_decimal(uint32_t ip);
  static void print_in_binary(uint32_t ip);

  friend std::ostream& operator<<(std::ostream& os, const IP& ip);

  // Getters
  uint32_t get_ip() const;
  uint8_t get_octet(int octet) const;
  char get_ip_class() const;

  // Setters
  void set_ip(uint32_t ip);
};

#endif
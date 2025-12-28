#ifndef IP_H
#define IP_H

#include <cstdint>
#include <ostream>

class IP;

struct IPBinaryView;
struct IPDecimalView;

class IP
{
private:
  uint32_t ip;

public:
  // Constructor
  IP(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4);
  IP(uint32_t full_ip);

  IPBinaryView to_binary() const;
  IPDecimalView to_decimal() const;

  // Getters
  uint32_t get_ip() const;
  uint8_t get_octet(int octet) const;
  char get_ip_class() const;

  // Setters
  void set_ip(uint32_t ip);

  bool is_private() const;
};

struct IPBinaryView
{
  const IP &ip;
};

struct IPDecimalView
{
  const IP &ip;
};

// stream operators
std::ostream &operator<<(std::ostream &os, const IPBinaryView &view);
std::ostream &operator<<(std::ostream &os, const IPDecimalView &view);
std::ostream &operator<<(std::ostream &os, const IP &ip);

#endif
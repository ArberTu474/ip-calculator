#include "ip.h"
#include <iostream>
#include <bitset>

IP::IP(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4)
{
  this->ip = 0;

  this->ip |= (uint32_t)o1 << 24; // first octet goes to the highest 8 bits
  this->ip |= (uint32_t)o2 << 16; // second octet
  this->ip |= (uint32_t)o3 << 8;  // third octet
  this->ip |= (uint32_t)o4 << 0;  // fourth octet stays in the lowest 8 bits
}

IP::IP(uint32_t ip) : ip(ip)
{
}

IPBinaryView IP::to_binary() const
{
  return IPBinaryView{*this};
}

IPDecimalView IP::to_decimal() const
{
  return IPDecimalView{*this};
}

std::ostream &operator<<(std::ostream &os, const IPBinaryView &view)
{
  uint32_t ip = view.ip.get_ip();

  os << std::bitset<8>((ip >> 24) & 0xFF) << '.'
     << std::bitset<8>((ip >> 16) & 0xFF) << '.'
     << std::bitset<8>((ip >> 8) & 0xFF) << '.'
     << std::bitset<8>(ip & 0xFF);

  return os;
}

std::ostream &operator<<(std::ostream &os, const IPDecimalView &view)
{
  uint32_t ip = view.ip.get_ip();

  os << ((ip >> 24) & 0xFF) << '.'
     << ((ip >> 16) & 0xFF) << '.'
     << ((ip >> 8) & 0xFF) << '.'
     << (ip & 0xFF);

  return os;
}

std::ostream &operator<<(std::ostream &os, const IP &ip)
{
  return os << IPDecimalView{ip};
}

uint32_t IP::get_ip() const
{
  return this->ip;
}

void IP::set_ip(uint32_t ip)
{
  this->ip = ip;
}

uint8_t IP::get_octet(int octet) const
{
  if (octet < 1 || octet > 4)
    return 0;

  int shift = (4 - octet) * 8;
  return static_cast<uint8_t>((ip >> shift) & 0xFF);
}

char IP::get_ip_class() const
{
  uint8_t o1 = (ip >> 24) & 0xFF;

  if ((o1 & 0b10000000) == 0)
    return 'A'; // 0xxxxxxx
  if ((o1 & 0b11000000) == 0b10000000)
    return 'B'; // 10xxxxxx
  if ((o1 & 0b11100000) == 0b11000000)
    return 'C'; // 110xxxxx
  if ((o1 & 0b11110000) == 0b11100000)
    return 'D'; // 1110xxxx

  return 'E'; // 1111xxxx
}

bool IP::is_private() const
{
  uint8_t o1 = (ip >> 24) & 0xFF;
  uint8_t o2 = (ip >> 16) & 0xFF;

  if (o1 == 10)
    return true;

  if (o1 == 172 && o2 >= 16 && o2 <= 31)
    return true;

  if (o1 == 192 && o2 == 168)
    return true;

  return false;
}
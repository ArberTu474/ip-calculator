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

std::ostream &operator<<(std::ostream &os, const IP &ip)
{
  os << static_cast<int>(ip.get_octet(1)) << "."
     << static_cast<int>(ip.get_octet(2)) << "."
     << static_cast<int>(ip.get_octet(3)) << "."
     << static_cast<int>(ip.get_octet(4));
  return os;
}

void IP::print_in_decimal() const
{
  uint8_t o1 = (ip >> 24) & 0b11111111;
  uint8_t o2 = (ip >> 16) & 0b11111111;
  uint8_t o3 = (ip >> 8) & 0b11111111;
  uint8_t o4 = ip & 0b11111111;

  printf("%u.%u.%u.%u", o1, o2, o3, o4);
}

void IP::print_in_binary() const
{
  uint8_t o1 = (ip >> 24) & 0b11111111;
  uint8_t o2 = (ip >> 16) & 0b11111111;
  uint8_t o3 = (ip >> 8) & 0b11111111;
  uint8_t o4 = ip & 0b11111111;

  printf("%s.%s.%s.%s",
         std::bitset<8>(o1).to_string().c_str(),
         std::bitset<8>(o2).to_string().c_str(),
         std::bitset<8>(o3).to_string().c_str(),
         std::bitset<8>(o4).to_string().c_str());
}

void IP::print_in_decimal(uint32_t ip)
{
  uint8_t o1 = (ip >> 24) & 0b11111111;
  uint8_t o2 = (ip >> 16) & 0b11111111;
  uint8_t o3 = (ip >> 8) & 0b11111111;
  uint8_t o4 = ip & 0b11111111;

  printf("%u.%u.%u.%u", o1, o2, o3, o4);
}

void IP::print_in_binary(uint32_t ip)
{
  uint8_t o1 = (ip >> 24) & 0b11111111;
  uint8_t o2 = (ip >> 16) & 0b11111111;
  uint8_t o3 = (ip >> 8) & 0b11111111;
  uint8_t o4 = ip & 0b11111111;

  printf("%s.%s.%s.%s",
         std::bitset<8>(o1).to_string().c_str(),
         std::bitset<8>(o2).to_string().c_str(),
         std::bitset<8>(o3).to_string().c_str(),
         std::bitset<8>(o4).to_string().c_str());
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

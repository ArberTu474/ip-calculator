# IP Calculator (Detyra 2)

Ky është një repo që përmban materialet për detyrën numër 2.

## Scripts për subnet calculator

Një skript për llogaritjen e subnet-eve që kërkova ishte një package `ipcalc`, që mund të aksesohet edhe nga ky [link](https://jodies.de/ipcalc).

### Infromacione të përgjithshme në lidhje me një ip

Mund të ekzekutojmë komandën e mëposhtme  për të marrë informacione të përgjithshme.

```bash
ipcalc 192.168.0.1
```

Dhe marrim një output të tillë:

```bash
Address:   192.168.0.1          11000000.10101000.00000000. 00000001
Netmask:   255.255.255.0 = 24   11111111.11111111.11111111. 00000000
Wildcard:  0.0.0.255            00000000.00000000.00000000. 11111111
=>
Network:   192.168.0.0/24       11000000.10101000.00000000. 00000000
HostMin:   192.168.0.1          11000000.10101000.00000000. 00000001
HostMax:   192.168.0.254        11000000.10101000.00000000. 11111110
Broadcast: 192.168.0.255        11000000.10101000.00000000. 11111111
Hosts/Net: 254                   Class C, Private Internet
```

Me komandën:

```bash
ipcalc 192.168.0.1 255.255.255.0 255.255.255.128
```

Mund të kalkulojmë subnetet e mundshme kur kalojmë nga `/24` në `/25`

```bash
Subnets after transition from /24 to /25

Netmask:   255.255.255.128 = 25 11111111.11111111.11111111.1 0000000
Wildcard:  0.0.0.127            00000000.00000000.00000000.0 1111111

 1.
Network:   192.168.0.0/25       11000000.10101000.00000000.0 0000000
HostMin:   192.168.0.1          11000000.10101000.00000000.0 0000001
HostMax:   192.168.0.126        11000000.10101000.00000000.0 1111110
Broadcast: 192.168.0.127        11000000.10101000.00000000.0 1111111
Hosts/Net: 126                   Class C, Private Internet

 2.
Network:   192.168.0.128/25     11000000.10101000.00000000.1 0000000
HostMin:   192.168.0.129        11000000.10101000.00000000.1 0000001
HostMax:   192.168.0.254        11000000.10101000.00000000.1 1111110
Broadcast: 192.168.0.255        11000000.10101000.00000000.1 1111111
Hosts/Net: 126                   Class C, Private Internet


Subnets:   2
Hosts:     252
```

## IP calculator Code

### Funksionalitetet e programit

- Identifikimi i [network id](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L10)
- Identifikimi i [broadcast id](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L31)
- Kalkulimi i [CIDR/ prefix length](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L113)
- Afishimi i [subnet mask](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L15)
- Afishimi i [wildcard mask](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L20)
- Identifikimi i [first host](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L37)
- Identifikimi i [last host](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L43)
- Kalkulimi i [total hosts](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L49)
- Kalkulimi i [usable hosts](https://github.com/ArberTu474/ip-calculator/blob/main/src/netëork.cpp#L58)
- Identifikimi i [network class](https://github.com/ArberTu474/ip-calculator/blob/main/src/ip.cpp#L77)
- Identifikimi nëse një [ip i përket një network](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L126)
- Identifikimi nëse një netëork është [private](https://github.com/ArberTu474/ip-calculator/blob/main/src/ip.cpp#L93)
- Identifikimi i [subnets në bazë të subnet bits](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L64)

### Implementimet

**[IP Class](https://github.com/ArberTu474/ip-calculator/blob/main/headers/ip.h)**

Çdo ip ruhet në një `uint32_t` type. Kjo është një prezantim binar i ip prej 32 bits.

```cpp
class IP
{
private:
  uint32_t ip;

public:
  // Constructor
  IP(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4);
  IP(uint32_t full_ip);
}
```

**[Network Class](https://github.com/ArberTu474/ip-calculator/blob/main/headers/network.h)**

Një `Network` është një kompozim ndërmjet 2 `IP`, pra ndërmjet një ip address dhe një subnet mask.

```cpp
class Network
{
private:
  IP ip_address;
  IP subnet_mask;

public:
  // Constructor
  Network(IP ip_address, IP subnet_mask);
}
```

Ky është një shembull se si mund të krijoht nje `Network`

```cpp
IP ip1(192, 168, 1, 10);
IP sm(255, 255, 255, 0);

Network n(ip1, sm);
```

### Metodat e klasave `Network` dhe `IP` 

#### Network::[get_network_id()](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L25-L29)

Për të llogaritur `network_id` duhet të përdorim operatorin logjik `AND` ndërmjet `subnet_mask` dhe `ip_address`

```
  11000000.10101000.00000001.00001010   192.168.1.10
& 11111111.11111111.11111111.00000000   255.255.255.0
=====================================
  11000000.10101000.00000001.00000000   192.168.1.0
```

Kur përdorim operatorin logjik `AND`, `subnet_mask` kryen rolin e nje filteri për `ip_address`. Çdo `0` në `subnet_mask` paraqet një bit që përdoret për hosts, çdo `1` paraqet bitet për `network_id`.

#### Network::[get_broadcast_id()](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L31-L35)

Për të llogaritur `broadcast_id` duhet të përdorim operatorin logjik `OR` ndërmjet `network_id` dhe `subnet_mask` të invertuar (`wildcard_mask`).

```
  11000000.10101000.00000001.00000000   192.168.1.0
| 00000000.00000000.00000000.11111111   0.0.0.255
=====================================
  11000000.10101000.00000001.11111111   192.168.1.255
```

`broadcat_id` është ip e fundit në një network range. `wildcard_mask` përfaqëson pjesën e ip që përdoret për të identifikuar hostet, por njëkohësisht në vlerë binare korespondon me hostin e fundit në një network, që është `broadcast_id`. Prandaj `wildcard_mask` i shtohet `network_id`.

#### Network::[get_prefix_length()](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L113-L124)

`prefix_length` ose `CIDR` paraqet numrin e biteve që korespondojnë me `network_id`. Për të llogaritur `CIDR` mjafton të numërojmë `1` që ndodhen në `subnet_mask`.

Ky është implementimi ne C++

```cpp
int Network::get_prefix_length() const
{
  uint32_t mask = subnet_mask.get_ip();
  int count = 0;

  while (mask)
  {
    // Nese LSB i mask eshte 0, couter rritet me 0
    // Nese LSB i mask eshte 1, counter rritet me 1
    // Operatori & ndermjet mask dhe 1 vendos nese counter rritet me 1 ose 0
    count += mask & 1;
    // zhvendosim me nje bit djathtas mask dhe e ruajme ate vlere prap ne mask.
    // Ne cdo vendosje loop-i numeron nje bit te ri
    mask >>= 1;
  }
  // loop-i do te iteroje 32 here, kur te kene ndodhur 32 zhvendosje djathtas. Ne kete moment mask do kete 32 bits me 0 dhe loop-i do te ndaloje.
  return count;
}
```

#### Network::[get_subnet_mask()](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L15-L18)

`subnet_mask` ofrohet tek konstruktori i `Network` dhe mund të aksesohet me një getter.

#### Network::[get_wildcard_mask()](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L20-L23)

`wildcard_mask` është inversi i `subnet_mask`.

```
~ 11111111.11111111.11111111.00000000   255.255.255.0
=====================================
  00000000.00000000.00000000.11111111   0.0.0.255
```

#### Network::[get_first_ip()](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L37-L41)

`first_ip` ështw ip e parë pas `network_id`, pra mund të llogaritet duke shtuar `1` tek `network_id`.

```
  11000000.10101000.00000001.00000000   192.168.1.0
+ 00000000.00000000.00000000.00000001             1
=====================================
  11000000.10101000.00000001.00000001   192.168.1.1
```

#### Network::[get_last_ip()](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L43-L47)

`last_ip` është ip e fundit e përdorshme në një network, ose ip që vjen para `broadcat_id`. Duke ditur këtë ne mund të heqim `1` për të llogaritur `last_ip`.

```
  11000000.10101000.00000001.11111111   192.168.1.255
- 00000000.00000000.00000000.00000001               1
=====================================
  11000000.10101000.00000001.00000001   192.168.1.254
```

#### Network::[get_total_hosts()](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L49-L56)

Nëse invertojmë bitet e `subnet_mask` marrim ato bite që përdoren për të identifikuar hostet. Nëse `subnet_mask` të invertuar i shtojmë `1` marrim numrin total të ip.

```
  00000000.00000000.00000000.11111111   = 255
+                                   1
=====================================
  00000000.00000000.00000001.00000000   = 256
```

#### Network::[get_usable_hosts()](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L58-L62)

Nga ip totale në një network 2 janë të rezervuara për `network_id` dhe `broadcast_id`.

#### IP::[get_ip_class()](https://github.com/ArberTu474/ip-calculator/blob/main/src/ip.cpp#L77-L91)

Klasat e ip mund të identifikohen duke parë oktetin e parë. Tabela mëposhtë paraqet rangein e çdo klase.

| Klasa | Bits e fillimit | Range per oktet-in e parë |
| ----- | --------------- | ------------------------- |
| A     | `0xxxxxxx`      | 0–127                     |
| B     | `10xxxxxx`      | 128–191                   |
| C     | `110xxxxx`      | 192–223                   |
| D     | `1110xxxx`      | 224–239                   |
| E     | `1111xxxx`      | 240–255                   |

Metoda është implementuar në këtë formë:

```cpp
char IP::get_ip_class() const
{
  uint8_t o1 = this->get_octet(1);

  // numrat 0b10000000, 0b11000000 etj, perdoren per te vecuar bite te caktuara.
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
```

#### Network::[is_ip_in_network(IP ip)](https://github.com/ArberTu474/ip-calculator/blob/main/src/network.cpp#L126-L144)

Që një ip të jetë pjesë e një network të caktuar bitet korespondues për `network_id` duhet të jenë të barabartë me `network_id`. `subnet_mask` veçon bitet për `network_id`.

```
ip: 11000000.10101000.00000001.00101000 = 192.168.1.40

ip & subnet_mask

  11000000.10101000.00000001.00101000   192.168.1.40
& 11111111.11111111.11111111.00000000   255.255.255.0
=====================================
  11000000.10101000.00000001.00000000   192.168.1.0

```

Rezultati i `ip & subnet_mask` është i barabartë me `network_id`, pra ip `192.168.1.40` ndodhet në këtë network.

#### IP::i[s_private()](https://github.com/ArberTu474/ip-calculator/blob/main/src/ip.cpp#L93-L108)

Klasat `A`, `B`, `C` kanë range me ip private. Tabela më poshtë paraqet këto range.

| Klasa | CIDR  | Range                           |
| ----- | ----- | ------------------------------- |
| A     | `/8`  | `10.0.0.0 – 10.255.255.255`     |
| B     | `/12` | `172.16.0.0 – 172.31.255.255`   |
| C     | `/16` | `192.168.0.0 – 192.168.255.255` |

- Që ip të jetë në klasen `A`: `o1 == 10`
- Që ip të jetë në klasën `B`: `o1 == 172 && 16 <= o2 <= 31`
- Që ip të jetë në klasën `C`: `o1 == 192 && o2 == 168`

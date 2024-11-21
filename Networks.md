# Networks
**NB:** '\>' means some kind of terminal promt.
## 27.09.2024
### startup password setup
``` 
> enable
> configure terminal  # enter global config mode
> line console 0  # config console
> password cisco
> login  # enable the password
> end
```
### user EXEC -> priveledged EXEC
```
> configure terminal
> enable secret class
> exit
```
### vty password
```
> configure terminal
> line vty 0 15
> password cisco
> login
> end
```
### encryption
```
> configure terminal
> service password-encryption
```
### config display & setup
```
> show running-config
> show startup-config
> copy running-config startup-config
```
### switch
SVI - swith virtual interface (for **remote** sw config)\
We need to assign both an IP and a default gateway.
```
> configure terminal
> interface vlan 1
> ip address 192.168.1.0 255.255.255.0
> no shutdown

switch# configure terminal
switch(config)# ip default-gateway 192.168.1.1
```
### setting up a router
```
> configure terminal
> interface G0/0/0
> description "SOHO LAN0 on G0/0/0"
> ip address 192.168.1.1 255.255.255.0
> ipv6 address ab12:bc:cd22:faaa:aa:cc:1:dd
> no shutdown
```
To ease local setup we assign a shorter local ipv6 address\
`> ipv6 address fe80::1:1`
### interface info
```
> show ip(v6) interface brief
> show ip(v6) route # routing table
> show interface G0/0
> show ip(v6) interfaces
```
## 11.10.2024
No calculators allowed on the final graded labs so you gotta learn to count quick.

ip: 192.168.10.1  11000000'10101000'00001010'00000001
subnet mask: 255.255.255.0 11111111'11111111'11111111'00000000

prefix: /24 - 24 ones L to R 11111111'11111111'11111111'00000000

**VLSM** - variable len subnet masking
subnets within subnets (e.g. /8 -> /16 -> /24)

```
> ping
> traceroute
```


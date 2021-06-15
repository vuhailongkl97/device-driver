sudo su
#wlan0 is my internet facing interface, eth5 is the BeagleBone USB connection
PC_IFACE=wlp2s0
BBB_IFACE=enx3403dea30136

ifconfig $BBB_IFACE 192.168.7.1
iptables --table nat --append POSTROUTING --out-interface $PC_IFACE -j MASQUERADE
iptables --append FORWARD --in-interface $BBB_IFACE  -j ACCEPT

echo 1 > /proc/sys/net/ipv4/ip_forward

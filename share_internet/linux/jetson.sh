sudo su
#wlan0 is my internet facing interface, eth5 is the BeagleBone USB connection
PC_IFACE=wlp2s0
JETSON_IFACE=enp0s20f0u4i5 

#ifconfig $JETSON_IFACE 192.168.55.100
iptables --table nat --append POSTROUTING --out-interface $PC_IFACE -j MASQUERADE
iptables --append FORWARD --in-interface $JETSON_IFACE  -j ACCEPT

echo 1 > /proc/sys/net/ipv4/ip_forward

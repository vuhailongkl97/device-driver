#wlan0 is my internet facing interface, eth5 is the BeagleBone USB connection
PC_IFACE=wlp2s0
JETSON_IFACE=enp0s20f0u4i5
JETSON_IFACE=enp0s20f0u1

ifconfig $JETSON_IFACE 192.168.55.100
iptables --table nat -I POSTROUTING --out-interface $PC_IFACE -j MASQUERADE
# for arch linux https://wiki.archlinux.org/title/Internet_sharing
iptables -A FORWARD -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT
iptables -I FORWARD --in-interface $JETSON_IFACE  -j ACCEPT

echo 1 > /proc/sys/net/ipv4/ip_forward

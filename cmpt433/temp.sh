#!/bin/bash

sudo iptables --table nat --append POSTROUTING --out-interface enp0s3 -j MASQUERADE
sudo iptables --append FORWARD --in-interface enx3403de7533ce -j ACCEPT
echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward

ssh -tt debian@192.168.7.2 <<EOF

	echo temppwd | sudo -S route add default gw 192.168.7.1

	echo nameserver 8.8.8.8 | sudo tee -a /etc/resolv.conf

	echo 'Completed setup!!!'
	ping google.ca

EOF

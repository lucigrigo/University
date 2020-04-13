#!/usr/bin/python2

import time
import sys

from mininet.log import setLogLevel
from mininet.net import Mininet
from mininet.topo import Topo
from mininet.util import dumpNodeConnections

import info


class SingleSwitchTopo(Topo):
    "Single switch connected to n hosts."
    def build(self, n=2):
        switch = self.addHost('router')
        # Python's range(N) generates 0..N-1
        for h in range(n):
            host = self.addHost(info.get("host_name", h))
            i1 = info.get("host_if_name", h)
            i2 = info.get("router_if_name", h)
            self.addLink(host, switch, intfName1=i1, intfName2=i2)


class NetworkManager(object):
    def __init__(self, net, n_hosts):
        self.net = net
        self.router = self.net.get("router")
        self.hosts = []
        for i in range(n_hosts):
            h = self.net.get(info.get("host_name", i))
            self.hosts.append(h)

    def setup_ifaces(self):
        for i in range(len(self.hosts)):
            host_ip = info.get("host_ip", i)
            router_ip = info.get("router_ip", i)

            self.router.setIP(router_ip, prefixLen=24, intf="r-{}".format(i))
            self.hosts[i].setIP(host_ip, prefixLen=24, intf="h-{}".format(i))

    def setup_macs(self):
        for i, host in enumerate(self.hosts):
            h_mac = info.get("host_mac", i)
            h_if = info.get("host_if_name", i)
            host.cmd("ifconfig {} hw ether {}".format(h_if, h_mac))

            r_mac = info.get("router_mac", i)
            r_if = info.get("router_if_name", i)
            self.router.cmd("ifconfig {} hw ether {}".format(r_if, r_mac))

    def disable_unneeded(self):
        def disable_ipv6(host):
            host.cmd('sysctl -w net.ipv6.conf.all.disable_ipv6=1')
            host.cmd('sysctl -w net.ipv6.conf.default.disable_ipv6=1')

        def disable_nic_checksum(host, iface):
            host.cmd('ethtool iface {} --offload rx off tx off'.format(iface))
            host.cmd('ethtool -K {} tx-checksum-ip-generic off'.format(iface))

        def disable_arp(host, iface):
            host.cmd("ip link set dev {} arp off".format(iface))

        disable_ipv6(self.router)
        for i, host in enumerate(self.hosts):
            disable_ipv6(host)
            h_if = info.get("host_if_name", i)
            disable_nic_checksum(host, h_if)


        # we want complete control over these actions
        self.router.cmd('echo "0" > /proc/sys/net/ipv4/ip_forward')
        self.router.cmd('echo "1" > /proc/sys/net/ipv4/icmp_echo_ignore_all')

    def add_default_routes(self):
        for i, host in enumerate(self.hosts):
            ip = info.get("router_ip", i)
            host.cmd("ip route add default via {}".format(ip))

    def add_hosts_entries(self):
        for host in self.hosts:
            for j in range(len(self.hosts)):
                ip = info.get("host_ip", j)
                host.cmd("echo '{} h{}' >> /etc/hosts".format(ip, j))

    def setup(self):
        self.disable_unneeded()
        self.setup_ifaces()
        self.setup_macs()
        self.add_hosts_entries()
        self.add_default_routes()

    def start_router(self):
        self.router.cmd("./router > {} 2>&1 &".format(info.LOGFILE))

    def run_test(self, testname):
        test = tests.TESTS[testname]
        for hp in test.hosts_p:
            h = self.net.get(info.get("host_name", hp))
            cmd = "python ./checker.py \
                    --passive \
                    --testname={} \
                    --host={}".format(testname, hp)
            self.hosts[hp].sendCmd(cmd)

        for ha in test.hosts_a:
            cmd = "python ./checker.py \
                    --active \
                    --testname={} \
                    --host={} &".format(testname, ha)
            self.hosts[ha].cmd(cmd)

        results = {}
        passed = True
        # XXX will this loop necessarily end?
        for hp in test.hosts_p:
            h = self.net.get(info.get("host_name", hp))
            # Somehow, somewhere, a newline is converted to a CRLF...
            results[h.name] = h.waitOutput().strip("\r\n")
            passed = passed and (results[h.name] == "PASS")

        return passed

def main():
    topo = SingleSwitchTopo(n=info.N_HOSTS)
    net = Mininet(topo)
    net.start()

    nm = NetworkManager(net, info.N_HOSTS)
    nm.setup()
    nm.start_router()

    net.startTerms()
    try:
        while 1:
            time.sleep(500)
    except KeyboardInterrupt:
        pass

    net.stop()


topos = { "mytopo": (lambda : SingleSwitchTopo()) }

if __name__ == "__main__":
    # Tell mininet to print useful information
    setLogLevel("info")
    main()

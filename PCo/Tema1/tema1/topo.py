#!/usr/bin/python2

import os
from pathlib import Path
import threading
import time
import signal
import sys

import tests
from mininet.log import setLogLevel
from mininet.net import Mininet
from mininet.topo import Topo
from mininet.util import dumpNodeConnections

import info


POINTS_PER_TEST = 5


def signal_handler(signal, frame):
    sys.exit(0)


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
        for i in range(len(self.hosts)):
            disable_arp(self.router, "r-{}".format(i))

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
        self.router.cmd("./router > {} 2> {} &".format(info.R_OUTFILE, info.R_ERRFILE))

    def run_test(self, testname):
        log = os.path.join(info.LOGDIR, testname)
        Path(log).mkdir(parents=True, exist_ok=True)

        test = tests.TESTS[testname]
        for hp in range(len(self.hosts)):
            lout = os.path.join(log, info.get("output_file", hp))
            lerr = os.path.join(log, info.get("error_file", hp))
            cmd = "./checker.py \
                    --passive \
                    --testname={} \
                    --host={} \
                    > {} \
                    2> {} &".format(testname, hp, lout, lerr)
            self.hosts[hp].cmd(cmd)

        time.sleep(info.TIMEOUT / 2)
        cmd = "./checker.py \
                --active \
                --testname={} \
                --host={} &".format(testname, test.host_s)
        self.hosts[test.host_s].cmd(cmd)

        results = {}
        time.sleep(info.TIMEOUT)
        for hp in range(len(self.hosts)):
            lout = os.path.join(log, info.get("output_file", hp))
            with open(lout, "r") as fin:
                results[hp] = fin.read().strip("\r\n")

        return results


def validate_test_results(results):
    passed = True
    for result in results.values():
        passed = passed and (result == "PASS")

    return passed


def main(run_tests=False):
    topo = SingleSwitchTopo(n=info.N_HOSTS)
    net = Mininet(topo)
    net.start()

    nm = NetworkManager(net, info.N_HOSTS)
    nm.setup()
    nm.start_router()
    time.sleep(1)

    max_points = POINTS_PER_TEST * len(tests.TESTS)
    total = 0

    print("{:=^80}\n".format(" Running tests "))
    if run_tests:
        for testname in tests.TESTS:
            results = nm.run_test(testname)
            passed = validate_test_results(results)
            crt_points = POINTS_PER_TEST if passed else 0
            total += crt_points
            str_status = "PASSED" if passed else "FAILED"
            str_points = "[{}/{}]".format(crt_points, POINTS_PER_TEST)
            print("{: >20} {:.>40} {: >8} {: >8}".format(testname, "", str_status,
                                                        str_points))
            time.sleep(info.TIMEOUT / 2)

        print("\nTOTAL: {}/{}\n".format(total, max_points))
    else:
        net.startTerms()
        signal.signal(signal.SIGINT, signal_handler)
        forever = threading.Event()
        forever.wait()

    net.stop()


if __name__ == "__main__":
    # Tell mininet to print useful information
    if len(sys.argv) > 1 and sys.argv[1] == "tests":
        main(run_tests=True)
    else:
        setLogLevel("info")
        main()

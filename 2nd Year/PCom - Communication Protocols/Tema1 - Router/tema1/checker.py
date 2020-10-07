#!/usr/bin/env python3
import argparse
import os
import shutil
import sys
import traceback

from scapy.sendrecv import sendp, sniff

import info
import tests


def capture(interface, output_file="test"):
    cap = sniff(iface=interface, timeout=info.TIMEOUT)

    # FIXME
    packets = []
    for i in range(len(cap)):
        packets.append(cap[i])

    return packets


def passive(host, testname):
    iface = info.get("host_if_name", host)
    packets = capture(iface)

    test = tests.TESTS[testname]
    if host == test.host_r:
        fn = test.passive_fn
    elif host == test.host_s:
        fn = tests.sender_default
    else:
        fn = tests.check_nothing

    try:
        status = fn(testname, packets)
    except AssertionError as e:
        traceback.print_tb(e.__traceback__)
        status = False

    if (status):
        print("PASS")
    else:
        print("FAIL")


def send_packets(packets, iface):
    for packet in packets:
        sendp(packet, iface=iface)


def active(host, testname):
    test = tests.TESTS[testname]
    iface = info.get("host_if_name", host)
    packets = test.active_fn(testname)
    send_packets(packets, iface)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--passive", action="store_true")
    parser.add_argument("--active", action="store_true")
    parser.add_argument("--testname", type=str)
    # Technically we *could* determine this, but this is simpler
    parser.add_argument("--host", type=int)
    args = parser.parse_args()
    assert(args.passive ^ args.active)
    if args.passive:
        passive(args.host, args.testname)
    else:
        active(args.host, args.testname)


if __name__ == "__main__":
    main()

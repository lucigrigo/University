N_HOSTS = 4
R_OUTFILE = "router_out.txt"
R_ERRFILE = "router_err.txt"
LOGDIR = "hosts_output"
ARP_TABLE = "arp_table.txt"

# If this is low there are bunch of annoying race conditions; this makes
# testing last veeeery long, but at least it's somewhat robust even on
# low-resource machines.
TIMEOUT = 4

BASE_FORMATS = {
        "host_name": "h-{}",
        "router_if_name": "r-{}",
        "host_if_name": "h-{}",
        "router_ip": "192.168.{}.1",
        "host_ip": "192.168.{}.2",
        "router_mac": "de:fe:c8:ed:00:{:02X}",
        "host_mac": "de:ad:be:ef:00:{:02X}",
        "output_file": "{}-host-out.txt",
        "error_file": "{}-host-err.txt",
}


def get(value, host):
    return BASE_FORMATS[value].format(host)

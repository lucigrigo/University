#!/usr/bin/env python3

import base64
import json
import gmpy2
import chardet


def str_to_num(text):
    """ Encodes a text to a long num representation (big endian). """
    return int.from_bytes(text.encode("ASCII"), 'big')

def num_to_str(flag):
    """ Decodes a text to a long num representation (big endian). """
    flag = int(flag)
    return flag.to_bytes((flag.bit_length() + 7) // 8, byteorder='big').decode('ASCII')

def encrypt(pub_k, flag):
    """ We only managed to steal this function... """
    cipher_flag = gmpy2.powmod(flag, pub_k["e"], pub_k["n"])
    # note: gmpy's to_binary uses a custom format (little endian + special GMPY header)!
    cipher_b64 = base64.b64encode(gmpy2.to_binary(cipher_flag))
    return cipher_b64

def decrypt(priv_k, cipher):
    """ We don't have the privary key, anyway :( """
    # you'll never get it!
    pass


if __name__ == "__main__":
    with open("message.txt", "r") as f:
        file_json = base64.b64decode(f.read())
        data = json.loads(file_json)

    flag = gmpy2.from_binary(base64.b64decode(data["flag"]))
    cipher = flag * gmpy2.powmod(2, data["e"], data["n"] )
    data["flag"] = base64.b64encode(gmpy2.to_binary(cipher)).decode('ascii')
    print(base64.b64encode(json.dumps(data).encode('ascii')).decode('ascii'))
    flag = b'\xa6\xe0\xca\xd2\xe6\xd0\x8c\xd8\xc2\xce\xf6\xde\x9a\xd2dl\xc4\x92\x94\xac\xf2\xc2l\xa0\x96\xd8f\xd6\xce\xce\x9e\x82\xa0hr\xb4\xca\x94\x8a\xecr\xcc\xb2\xfa'
    flag = str(bytearray([b // 2 for b in flag]), 'utf-8')
    print(flag)

"""
This module runs the homework's solution on a given testfile

Computer Systems Architecture Course
Assignment 1
March 2020
"""

import sys
from json import loads

from tema.producer import Producer
from tema.consumer import Consumer
from tema.marketplace import Marketplace
from tema.product import Product, Coffee, Tea

def main():
    """
        Convert the market_configuration input file into specific models:
        Producer, Consumer, Marketplace
    """
    try:
        filename = sys.argv[1]
    except IndexError:
        print("no input file specified")
        raise SystemExit

    with open(filename) as input_file:
        market_config = loads(input_file.read())

    # turn product definitions into actual products
    products = {}

    for k, products_dict in market_config['products'].items():
        params = {k: products_dict[k] for k in products_dict.keys() if k != 'product_type'}
        products[k] = globals()[products_dict['product_type']](**params)
    del market_config['products']

    # turn product ids into products in producers
    for producer in market_config['producers']:
        producer['products'] = [(products[i], quantity, sleep_time)
                                for i, quantity, sleep_time
                                in producer['products']]

    # turn product ids into products in consumer order lists and expected carts
    for consumer in market_config['consumers']:
        for cart in consumer['carts']:
            for operation in cart:
                operation['product'] = products[operation['product']]

    # build the marketplace
    marketplace = Marketplace(**market_config['marketplace'])

    # build and start the producers
    producers = [Producer(**p_market_config, marketplace=marketplace, daemon=True)
                 for p_market_config in market_config['producers']]

    for producer in producers:
        producer.start()

    # build and start the consumers
    consumers = [Consumer(**c_market_config, marketplace=marketplace)
                 for c_market_config in market_config['consumers']]

    for consumer in consumers:
        consumer.start()

    for consumer in consumers:
        consumer.join()


if __name__ == '__main__':
    main()

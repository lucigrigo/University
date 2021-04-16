"""
Grigore Lucian-Florin 336CA

This module represents the Producer.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Thread
import time


class Producer(Thread):
    """
    Class that represents a producer.
    """

    def __init__(self, products, marketplace, republish_wait_time, **kwargs):
        """
        Constructor.

        @type products: List()
        @param products: a list of products that the producer will produce

        @type marketplace: Marketplace
        @param marketplace: a reference to the marketplace

        @type republish_wait_time: Time
        @param republish_wait_time: the number of seconds that a producer must
        wait until the marketplace becomes available

        @type kwargs:
        @param kwargs: other arguments that are passed to the Thread's __init__()
        """
        Thread.__init__(self, **kwargs)

        self.products = products  # own products
        self.marketplace = marketplace  # link to marketplace
        self.republish_wait_time = republish_wait_time  # time to wait when publish fails

        self.own_id = marketplace.register_producer()  # registering into the market

    def run(self):
        while True:
            # iterating through own products
            for (product, no_products, wait_time) in self.products:
                i = 0

                # a product can be published multiple times
                while i < no_products:
                    # checking if the operation had success
                    if self.marketplace.publish(self.own_id, product):
                        time.sleep(wait_time)
                        i += 1
                    else:
                        # if not, current thread sleeps for the according amount of time
                        time.sleep(self.republish_wait_time)

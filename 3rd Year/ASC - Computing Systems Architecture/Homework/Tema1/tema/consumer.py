"""
Grigore Lucian-Florin 336CA

This module represents the Consumer.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Thread
import time


class Consumer(Thread):
    """
    Class that represents a consumer.
    """

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        """
        Constructor.

        :type carts: List
        :param carts: a list of add and remove operations

        :type marketplace: Marketplace
        :param marketplace: a reference to the marketplace

        :type retry_wait_time: Time
        :param retry_wait_time: the number of seconds that a producer must wait
        until the Marketplace becomes available

        :type kwargs:
        :param kwargs: other arguments that are passed to the Thread's __init__()
        """
        Thread.__init__(self, **kwargs)

        self.carts = carts  # carts that this consumer needs
        self.marketplace = marketplace  # link to marketplace
        self.retry_wait_time = retry_wait_time  # cooldown when an action fails

        # dict to hold consumer specific actions
        self.actions = {
            'add': self.marketplace.add_to_cart,
            'remove': self.marketplace.remove_from_cart
        }

    def run(self):
        # iterating through carts
        for cart in self.carts:
            # registering cart
            cart_id = self.marketplace.new_cart()

            # iterating through current cart operations
            for operation in cart:
                iters = 0

                # adding a product as many times as it is needed
                while iters < operation['quantity']:
                    ret = self.actions[operation['type']](
                        cart_id, operation['product'])

                    # if the operation fails, consumer tries again after cooldown
                    if ret or ret is None:
                        iters += 1
                    else:
                        time.sleep(self.retry_wait_time)

            # placing order at the marketplace
            self.marketplace.place_order(cart_id)

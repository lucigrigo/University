"""
Grigore Lucian-Florin 336CA

This module represents the Marketplace.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import currentThread, Lock


class Marketplace:
    """
    Class that represents the Marketplace. It's the central part of the implementation.
    The producers and consumers use its methods concurrently.
    """

    def __init__(self, queue_size_per_producer):
        """
        Constructor

        :type queue_size_per_producer: Int
        :param queue_size_per_producer: the maximum size of a queue associated with each producer
        """
        self.queue_size_per_producer = queue_size_per_producer  # max no. of items per producer
        self.producer_queues = []  # no. of items of each producer
        self.all_products = []  # list with all products from all producers
        self.producted_by = dict()  # stores (product, producer) information
        self.no_carts = 0  # no. of carts, i.e. their ids
        self.carts = dict()  # stores (cart_id, list of products) information

        self.producer_lock = Lock()  # lock used when registering a producer
        self.consumer_lock = Lock()  # lock used when registering a consumer (a new cart)
        self.cart_lock = Lock()  # lock used for removing products from cart

    def register_producer(self):
        """
        Returns an id for the producer that calls this.
        """
        # locking correspondent lock
        with self.producer_lock:
            # creating new id
            producer_id = len(self.producer_queues)
            self.producer_queues.append(0)

            return producer_id

    def publish(self, producer_id, product):
        """
        Adds the product provided by the producer to the marketplace

        :type producer_id: String
        :param producer_id: producer id

        :type product: Product
        :param product: the Product that will be published in the Marketplace

        :returns True or False. If the caller receives False, it should wait and then try again.
        """
        # current producer has already reached the limit for no. of items published
        if self.producer_queues[producer_id] >= self.queue_size_per_producer:
            return False

        # adding product to current producer's count
        self.producer_queues[producer_id] += 1
        self.producted_by[product] = producer_id

        # adding product to the list of products
        self.all_products.append(product)

        return True

    def new_cart(self):
        """
        Creates a new cart for the consumer

        :returns an int representing the cart_id
        """
        # registering a new cart
        with self.consumer_lock:
            # creating a new id
            cart_id = self.no_carts
            self.no_carts += 1

        # making the dict entry hold a list by default
        self.carts.setdefault(cart_id, [])

        return cart_id

    def add_to_cart(self, cart_id, product):
        """
        Adds a product to the given cart. The method returns

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to add to cart

        :returns True or False. If the caller receives False, it should wait and then try again
        """
        # extracting product from the list
        with self.cart_lock:
            if product not in self.all_products:
                return False

            # removing product from its producer queue size
            self.producer_queues[self.producted_by[product]] -= 1

            # removing product from the list
            self.all_products.remove(product)

        # adding product to cart
        self.carts[cart_id].append(product)

        return True

    def remove_from_cart(self, cart_id, product):
        """
        Removes a product from cart.

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to remove from cart
        """
        # removing product from cart
        self.carts[cart_id].remove(product)

        # appending product to the list with all the products
        self.all_products.append(product)

        # increasing queue size for its producer
        self.producer_queues[self.producted_by[product]] += 1

    def place_order(self, cart_id):
        """
        Return a list with all the products in the cart.

        :type cart_id: Int
        :param cart_id: id cart
        """
        # removing list of products identified by the cart's id
        products = self.carts.pop(cart_id, None)

        # printing products
        for product in products:
            print(f'{currentThread().getName()} bought {product}')

        return products

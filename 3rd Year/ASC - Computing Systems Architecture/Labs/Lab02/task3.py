"""
Coffee Factory: A multiple producer - multiple consumer approach

Generate a base class Coffee which knows only the coffee name
Create the Espresso, Americano and Cappuccino classes which inherit the base class knowing that
each coffee type has a predetermined size.
Each of these classes have a get message method

Create 3 additional classes as following:
    * Distributor - A shared space where the producers puts coffees and the consumers takes them
    * CoffeeFactory - An infinite loop, which always sends coffees to the distributor
    * User - Another infinite loop, which always takes coffees from the distributor

The scope of this exercise is to correctly use threads, classes and synchronization objects.
The size of the coffee (ex. small, medium, large) is chosen randomly everytime.
The coffee type is chosen randomly everytime.

Example of output:

Consumer 65 consumed espresso
Factory 7 produced a nice small espresso
Consumer 87 consumed cappuccino
Factory 9 produced an italian medium cappuccino
Consumer 90 consumed americano
Consumer 84 consumed espresso
Factory 8 produced a strong medium americano
Consumer 135 consumed cappuccino
Consumer 94 consumed americano
"""

from time import sleep
from threading import Thread, Semaphore
import random

class Coffee:
    def __init__(self, name, size):
        self.__name__ = name
        self.__size__ = size

    def get_name(self):
        return self.__name__

    def get_size(self):
        return self.__size__

class Espresso(Coffee):
    def __init__(self, size):
        Coffee.__init__(self, 'espresso', size)

    def get_message(self):
        return f'strong {self.get_size()} {self.get_name()}'

class Americano(Coffee):
    def __init__(self, size):
        Coffee.__init__(self, 'americano', size)

    def get_message(self):
        return f'tasty {self.get_size()} {self.get_name()}'

class Cappuccino(Coffee):
    def __init__(self, size):
        Coffee.__init__(self, 'cappuccino', size)

    def get_message(self):
        return f'stylish {self.get_size()} {self.get_name()}'

class Distributor:
    def __init__(self, size):
        self.__size__ = size
        self.mutex_prod = Semaphore(1)
        self.mutex_cons = Semaphore(1)
        self.empty = Semaphore(value=size)
        self.full = Semaphore(0)
        self.buffer = [None] * size
        self.last = 0
        self.first = 0

    def get(self):
        self.full.acquire()
        x = None 

        with self.mutex_cons:
            x = self.buffer[self.first]
            self.first = (self.first + 1) % self.__size__
        
        self.empty.release()
        return x

    def put(self, coffee):
        self.empty.acquire()

        with self.mutex_prod:
            self.buffer[self.last] = coffee
            self.last = (self.last + 1) % self.__size__
        
        self.full.release()
    
class CoffeeFactory(Thread):
    def __init__(self, id, buffer, available_sizes, available_coffees):
        Thread.__init__(self)
        self.__id__ = id
        self.__buffer__ = buffer
        self.__available_sizes__ = available_sizes
        self.__available_coffees__ = available_coffees

    def run(self):
        while True:
            size = random.choice(self.__available_sizes__)
            coffee_type = random.choice(self.__available_coffees__)
            coffee = coffee_type(size)

            print(f'Producer {self.__id__} produced ' + coffee.get_message())
            
            self.__buffer__.put(coffee)
            sleep(1)


class User(Thread):
    def __init__(self, id, buffer):
        Thread.__init__(self)
        self.__id__ = id
        self.__buffer__ = buffer
    
    def run(self):
        while True:
            coffee = self.__buffer__.get()
            print(f'Consumer {self.__id__} consumed a ' + coffee.get_message())
            sleep(1)

if __name__ == '__main__':
    available_coffees = [Espresso, Americano, Cappuccino]
    available_sizes = ['small', 'medium', 'large']

    no_producers = int(input('How many producers? '))
    no_consumers = int(input('How many consumers? '))
    buffer_size = int(input('How big should the buffer be? '))

    buffer = Distributor(buffer_size)

    producers = [CoffeeFactory(i, buffer, available_sizes, available_coffees) for i in range(no_producers)]
    consumers = [User(i, buffer) for i in range(no_consumers)]

    for p in producers:
        p.start()
    
    for c in consumers:
        c.start()

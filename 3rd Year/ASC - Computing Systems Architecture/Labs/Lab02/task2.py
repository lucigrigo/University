"""
    Basic thread handling exercise:

    Use the Thread class to create and run more than 10 threads which print their name and a random
    number they receive as argument. The number of threads must be received from the command line.

    e.g. Hello, I'm Thread-96 and I received the number 42

"""

from threading import Thread
from random import randint, seed

def msg(index, nr):
    print('Hello, I am Thread #' + str(index) + ' and I received the number ' + str(nr))

if __name__ == '__main__':
    no_threads = int(input('Nr de threaduri? '))

    threads = []
    seed()

    for i in range(no_threads):
        nr = randint(0, no_threads * no_threads)
        thr = Thread(target = msg, args = (i, nr))
        threads.append(thr)
    
    for t in threads:
        t.start()

    for t in threads:
        t.join()

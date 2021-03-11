from threading import Thread, Lock
from time import sleep
from random import randint

class Philosopher(Thread):
    def __init__(self, id, left_fork, right_fork):
        Thread.__init__(self)
        self.id = id
        self.left_fork = left_fork
        self.right_fork = right_fork

    def run(self):
        while True:
            with self.left_fork:
                sleep(0.1)
                result = self.right_fork.acquire(False)
                
                if result == True:
                    break

            self.left_fork, self.right_fork = self.right_fork, self.left_fork

        print(f'Philosopher {self.id} is eating')

        self.right_fork.release()

if __name__ == '__main__':
    no_philosophers = int(input('How many Philosophers? '))
    
    forks = [Lock() for _ in range(no_philosophers)]
    philosophers = [Philosopher(i, forks[i - 1], forks[i]) for i in range(no_philosophers)]

    for p in philosophers:
        p.start()
    
    for p in philosophers:
        p.join()
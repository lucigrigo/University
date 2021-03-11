from random import randint, seed
from threading import Semaphore, Thread
from time import sleep

def access(nr, sem):
    sem.acquire()
    print ("Thread-ul", nr, " acceseaza")
    sleep(randint(1, 4))
    print ("Thread-ul", nr, " a terminat")
    sem.release()

# initializam semaforul cu 3 pentru a avea maxim 3 thread-uri active la un moment dat
semafor = Semaphore(value = 3)

# stocam obiectele Thread pentru a putea face join
thread_list = []

seed() # seed-ul este current system time pentru generatorul de nr random

# pornim thread-urile
for i in range(10):
    thread = Thread(target = access, args = (i, semafor))
    thread.start()
    thread_list.append(thread)

# asteptam terminarea thread-urilor
for i in range(len(thread_list)):
    thread_list[i].join()
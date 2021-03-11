
    

    from threading import Thread
  
def my_concurrent_code(nr, msg):
    """ Functie care va fi rulata concurent """
    print ("Thread", nr, "says:", msg)

# creeaza obiectele corespunzatoare thread-urilor
t1 = Thread(target = my_concurrent_code, args = (1, "hello from thread"))
t2 = Thread(target = my_concurrent_code, args = (2, "hello from other thread"))

# porneste thread-urile
t1.start()
t2.start()

# executia thread-ului principal continua de asemenea
print ("Main thread says: hello from main")

# asteapta terminarea thread-urilor
t1.join()
t2.join()
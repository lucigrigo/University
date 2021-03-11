
    

    from threading import Thread
  
class MyThread(Thread):
    """ Clasa care incapsuleaza codul nostru concurent """
    def __init__(self, nr, msg):
        Thread.__init__(self)
        self.nr = nr
        self.msg = msg

    def run(self):
        print ("Thread", self.nr, "says:", self.msg)

# creeaza obiectele corespunzatoare thread-urilor
t1 = MyThread(1, "hello from thread")
t2 = MyThread(2, "hello from other thread")

# porneste thread-urile
t1.start()
t2.start()

# executia thread-ului principal continua de asemenea
print ("Main thread says: hello from main")

# asteapta terminarea thread-urilor
t1.join()
t2.join()
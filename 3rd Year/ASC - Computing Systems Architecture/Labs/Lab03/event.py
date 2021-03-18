from threading import enumerate, Condition, Event, Thread

class Master(Thread):
    def __init__(self, max_work, work):
        Thread.__init__(self, name = "Master")
        self.max_work = max_work
        self.work = work
        self.first_work = False
    
    def set_worker(self, worker):
        self.worker = worker
    
    def run(self):
        for i in range(self.max_work):
            with self.work:
                self.w = i
                self.first_work = True
                self.work.notify()
                self.work.wait()
                if self.get_work() + 1 != self.worker.get_result():
                    print ("oops")
                print ("%d -> %d" % (self.w, self.worker.get_result()))
    
    def get_work(self):
        return self.w

class Worker(Thread):
    def __init__(self, terminate,work):
        Thread.__init__(self, name = "Worker")
        self.terminate = terminate
        self.work = work

    def set_master(self, master):
        self.master = master
    
    def run(self):
        while(True):
            with self.work:
                if not self.master.first_work:
                    self.work.wait()
                    self.master.first_work = False
                if terminate.is_set():
                    break
                self.result = self.master.get_work() + 1
                self.work.notify()
    
    def get_result(self):
        return self.result

if __name__ ==  "__main__":
    # create shared objects
    terminate = Event()
    work = Condition()
    
    # start worker and master
    w = Worker(terminate, work)
    m = Master(10, work)
    w.set_master(m)
    m.set_worker(w)
    w.start()
    m.start()

    # wait for master
    m.join()

    # wait for worker
    with work:
        terminate.set()
        work.notifyAll()
    w.join()

    # print running threads for verification
    print(enumerate())


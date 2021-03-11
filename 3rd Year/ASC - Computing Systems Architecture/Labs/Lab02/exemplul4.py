from threading import RLock, Thread

def inc(lista, rlock, index, n):
    """ Incrementeaza elementul index din lista de n ori """
    rlock.acquire()
    if n > 0:
        lista[index] += 1               # incrementeaza o data
        inc(lista, rlock, index, n - 1) # incrementeaza recursiv de n-1 ori
    rlock.release()

def dec(lista, rlock, index, n):
    """ Decrementeaza elementul index din lista de n ori """
    rlock.acquire()
    if n > 0:
        lista[index] -= 1               # decrementeaza o data
        dec(lista, rlock, index, n - 1) # decrementeaza recursiv de n-1 ori
    rlock.release()

# lista si lock-ul care o protejeaza
my_list = [0]
my_lock = RLock()

# thread-urile care modifica elemente din lista
t1 = Thread(target = inc, args = (my_list, my_lock, 0, 100))
t2 = Thread(target = dec, args = (my_list, my_lock, 0, 100))

# lista inainte de modificari
print (my_list)

t1.start()
t2.start()

t1.join()
t2.join()

# lista dupa modificari
print (my_list)
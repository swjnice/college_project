import time
import random


def QuickSort(T, p, r):
    if p<r:
        q = Partition(T,p,r)
        QuickSort(T,p,q-1)
        QuickSort(T,q+1,r)

def Partition(T, p, r):
    x = T[r]
    i = p
    for j in range(p,r):
        if T[j] <= x:
            T[i], T[j] = T[j], T[i]
            i += 1
    T[i], T[r] = T[r], T[i]
    return i


def Run_QuickSort(k):
    T = [0]*k
    for i in range(len(T)):
        T[i] = random.randint(0, k)

    start = time.time()
    QuickSort(T,0,len(T)-1)
    end = time.time() - start

    Sorted = True
    for i in range(1, len(T)):
        if T[i] < T[i-1]:
            Sorted = False

    print "Number of input : ", len(T)
    print "Is it Sorted? : ", Sorted
    print "Time : ", end, '\n'


print "\x1b[1;32mQUICKSORT\x1b[1;m" '\n'*2
Run_QuickSort(100)
Run_QuickSort(1000)
Run_QuickSort(10000)





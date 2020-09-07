import time
import random

def InsertionSort(T):
    l = len(T)
    for i in range(0,l-1):
        x = T[i+1]
        j = i
        while j >= 0:
            if T[j] > x:
                T[j+1] = T[j]
                j = j - 1
            else:
               
                break
        if j == -1:
            T[0] = x
        else:
            T[j] = x

def Run_InsertionSort(k):
    T = [0]*k
    for i in range(len(T)):
        T[i] = random.random()

    start = time.time()
    InsertionSort(T)
    end = time.time() - start

    Sorted = True
    for i in range(1,len(T)):
        if T[i]<T[i-1]:
            Sorted = False

    print "Number of input : ", len(T)
    print"Is it Sorted?? : ", Sorted
    print"Time : ", end, '\n'


print "\x1b[1;32mInsertionSort\x1b[1;m"'\n' *2
Run_InsertionSort(100)
Run_InsertionSort(1000)
Run_InsertionSort(10000)

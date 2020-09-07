import time
import random

def max_heapify(T,i,heap_size):
    l = (i+1)*2
    r = (i+1)*2 + 1

    if l <= heap_size and T[l-1] > T[i]:
        largest = l-1
    else:
        largest = i
    if r <= heap_size and T[r-1] > T[largest]:
        largest = r-1
    if largest != i:
        T[i], T[largest] = T[largest], T[i]
        max_heapify(T, largest, heap_size)

def build_max_heap(T):
    heap_size = len(T)
    for i in range(heap_size/2-1, -1, -1):
        max_heapify(T, i, heap_size)
    

def HeapSort(T):
    build_max_heap(T)
    heap_size = len(T)
    while heap_size > 1 :
        T[0], T[heap_size-1] = T[heap_size-1], T[0]
        heap_size = heap_size - 1
        max_heapify(T,0,heap_size)

def Run_HeapSort(k):
    T = [0]*k
    for i in range(len(T)):
        T[i] = random.randint(0, k)

    start = time.time()
    HeapSort(T)
    end = time.time() - start

    Sorted = True
    for i in range(1, len(T)):
        if T[i] < T[i-1]:
            Sorted = False

    print "Number of input : ", len(T)
    print "Is it Sorted? : ", Sorted
    print "Time : ", end, '\n'*2

print '\x1b[1;32mHeapSort\x1b[1;m' '\n' *2
Run_HeapSort(100)
Run_HeapSort(1000)
Run_HeapSort(10000)

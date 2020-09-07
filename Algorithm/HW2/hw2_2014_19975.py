#! /usr/bin/env python3

import sys
import argparse
import numpy as np
import time


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--K', default=5, type=int, help='The number of the lists')
    parser.add_argument('--N', default=4, type=int, help='The number of the elements per each list')
    parser.add_argument('--max_number', default=50000, type=int, help='The maximum element for the array')

    args = parser.parse_args()

    return args


def generate_array(max_n, K, N):
    X = np.random.choice(max_n,size=(K, N),replace=False)
    X = np.sort(X,axis=-1)
    return X


### functions for Quicksort ###
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




def naive_sorting(X):
    '''
    ############################ Function description #################################

    Design a naive sorting algorithm (e.g., quick sort, merge sort, etc.) for this task.
    In this case, the worst case time complexity will be O(KNlog(KN)).

    ###################################################################################
    '''
    sorted_array = []
    for j in range(len(X)):
        for ele in X[j]:
            sorted_array.append(ele)
    ##### Please write your code down here #####
    QuickSort(sorted_array, 0, len(sorted_array)-1)

    return sorted_array




### funcions for minheap ####

class Node:
    number = 0
    arraypos = 0
    extract = 0

    def __init__(self, number, arraypos, extract):
        self.number = number
        self.arraypos = arraypos
        self.extract = extract

def min_heapify(T,i,heap_size):
    l = (i+1)*2
    r = (i+1)*2 + 1

    if l <= heap_size and T[l-1].number < T[i].number:
        smallest = l-1
    else:
        smallest = i
    if r <= heap_size and T[r-1].number < T[smallest].number:
        smallest = r-1
    if smallest != i:
        T[i], T[smallest] = T[smallest], T[i]
        min_heapify(T, smallest, heap_size)

def build_min_heap(T):
    heap_size = len(T)
    for i in range(int(heap_size/2), -1, -1):
        min_heapify(T, i, heap_size)

def proposed_algorithm(X):
    '''
    ############################ Function description ################################

    The above approach does not take advantage of the fact that each list is already
    sorted. However, there is a way to solve this problem more efficiently.
    Design an algorithm to solve this task in O(KNlog(K)) by using min-heap.

    ###################################################################################
    '''
    sorted_array = []
    ##### Please write your code down here #####
    min_heap_array = []
    for first in range(len(X)):
        min_heap_array.append(Node(X[first][0], first, 0))
    build_min_heap(min_heap_array)
    
    while len(min_heap_array) != 0:
        min_heapify(min_heap_array, 0, len(min_heap_array))
        sorted_array.append(min_heap_array[0].number)
        min_heap_array[0].extract += 1
        if (min_heap_array[0].extract == len(X[0])):
            min_heap_array[0] = min_heap_array[len(min_heap_array)-1]
            del min_heap_array[len(min_heap_array)-1]
        else:
            min_heap_array[0].number = X[min_heap_array[0].arraypos][min_heap_array[0].extract]
  
    return sorted_array



def check_correctness(X,Y):
    return np.array_equal(X,Y)




if __name__ == '__main__':

    # The input will be randomly changed by TAs when grading
    # The default K, N are set as the example in the homework pdf.
    # If you execute <python3 hw2.py>, the arguments will be set by the default.
    # You can also use your own K, N by executing command  <python3 hw2.py --K k --N n>
    # Ex) python3 hw2.py --K 10 --N 5
    sys.setrecursionlimit(1000000000)
    args = parse_args()
    max_number = args.max_number
    K = args.K
    N = args.N

    Input_Array = generate_array(max_number, K, N)
    ##print('Input Size : {:d}, {:d}'.format(K, N))
    ##print('Input Array : {}'.format(Input_Array))

    start_time = time.time()
    sorted_array_A = naive_sorting(Input_Array)
    execute_time = time.time()
    ##print('Sorted List : {}'.format(sorted_array_A))
    print('Time for the naive sorting : {:f}'.format(execute_time-start_time))

    start_time = time.time()
    sorted_array_B = proposed_algorithm(Input_Array)
    execute_time = time.time()
    ##print('Sorted List : {}'.format(sorted_array_B))
    print('Time for the proposed algorithm : {:f}'.format(execute_time-start_time))

    correct = check_correctness(sorted_array_A, sorted_array_B)
    if correct:
        print('Your Algortim is Correct')
    else:
        print('Please Try Again')

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



def naive_sorting(X):
    '''
    ############################ Function description #################################

    Design a naive sorting algorithm (e.g., quick sort, merge sort, etc.) for this task.
    In this case, the worst case time complexity will be O(KNlog(KN)).

    ###################################################################################
    '''
    sorted_array = 
    ##### Please write your code down here #####

    return sorted_array


def proposed_algorithm(X):
    '''
    ############################ Function description ################################

    The above approach does not take advantage of the fact that each list is already
    sorted. However, there is a way to solve this problem more efficiently.
    Design an algorithm to solve this task in O(KNlog(K)) by using min-heap.

    ###################################################################################
    '''
    sorted_array = 
    ##### Please write your code down here #####

    return sorted_array


def check_correctness(X,Y):
    return np.array_equal(X,Y)




if __name__ == '__main__':

    # The input will be randomly changed by TAs when grading
    # The default K, N are set as the example in the homework pdf.
    # If you execute <python3 hw2.py>, the arguments will be set by the default.
    # You can also use your own K, N by executing command  <python3 hw2.py --K k --N n>
    # Ex) python3 hw2.py --K 10 --N 5

    args = parse_args()
    max_number = args.max_number
    K = args.K
    N = args.N

    Input_Array = generate_array(max_number, K, N)
    print('Input Size : {:d}, {:d}'.format(K, N))
    print('Input Array : {}'.format(Input_Array))

    start_time = time.time()
    sorted_array_A = naive_sorting(Input_Array)
    execute_time = time.time()
    print('Sorted List : {}'.format(sorted_array_A))
    print('Time for the naive sorting : {:f}'.format(execute_time-start_time))

    start_time = time.time()
    sorted_array_B = proposed_algorithm(Input_Array)
    execute_time = time.time()
    print('Sorted List : {}'.format(sorted_array_B))
    print('Time for the proposed algorithm : {:f}'.format(execute_time-start_time))

    correct = check_correctness(sorted_array_A, sorted_array_B)
    if correct:
        print('Your Algortim is Correct')
    else:
        print('Please Try Again')

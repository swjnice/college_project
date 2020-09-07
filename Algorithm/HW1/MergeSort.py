import sys
import time
import random
t1 = sys.maxsize

def MergeSort(T,p,r):
     if p<r:
         q = (p+r)/2
         MergeSort(T,p,q)
         MergeSort(T,q+1,r)
         Merge(T,p,q,r)
 
def Merge(T, p, q, r):
    n1 = q-p+1
    n2 = r-q
    Left = [0]*(n1+1)
    Right = [0]*(n2+1)

    for i in range(n1):
        Left[i] = T[p+i]
    for j in range(n2):
        Right[j] = T[q+j+1] 
    
    Left[n1] = t1
    Right[n2] = t1

    i=0
    j=0

    for k in range(p,r+1):
        if Left[i] <= Right[j]:
            T[k] = Left[i]
            i=i+1
        else:
            T[k] = Right[j]
            j=j+1


def Run_MergeSort(k):
    T = [0]*100
    for i in range(len(T)):
        T[i] = random.randint(0, 100)

    start = time.time()
    MergeSort(T,0,len(T)-1)
    end = time.time() - start

    Sorted = True
    for i in range(1, len(T)):
        if T[i] < T[i-1]:
            Sorted = False

    print "Number of input : ", len(T)
    print "Is it Sorted? : ", Sorted
    print "Time : ", end, '\n'




print "\x1b[1;32mMERGESORT\x1b[1;m"'\n'*2
Run_MergeSort(100)
Run_MergeSort(1000)
Run_MergeSort(10000)



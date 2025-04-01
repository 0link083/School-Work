import matplotlib.pyplot as plt
import math
import random
import time

# global variables
myCount = 0
basicOpsCountMergeSort = []
basicOpsCountQuickSort = []
runTimesMergeSort = []
runTimesQuickSort = []
estimatedTimesMergeSort = []
estimatedTimesQuickSort = []


def reset():
    global myCount
    myCount = 0


def basicOps():
    return myCount

#######################################################################################################################
#  MERGE_SORT FUNCTION(S)
def mergeSort(a): #   parameter a is a list of items to sort in non-decreasing order
    n = len(a)

    if n > 1:
        mid = n // 2
        b = a[:mid]  # python slicing, p.47
        c = a[mid:]
        mergeSort(b)
        mergeSort(c)
        merge(a, b, c)
    return a  # because it is an empty list or single item


def merge(a, b, c):
    global myCount
    n = len(a)
    m = n // 2
    i = j = k = 0  # initialized variables

    while j < m and k < n - m:
        myCount += 1
        if b[j] <= c[k]:
            a[i] = b[j]
            j += 1
        else:
            a[i] = c[k]
            k += 1
        i += 1

    while j < len(b):
        a[i] = b[j]
        i += 1
        j += 1

    while k < len(c):
        a[i] = c[k]
        i += 1
        k += 1

    return a

#######################################################################################################################
#  QUICK_SORT FUNCTION(S)
def quickSort(listToSort, low, high):
    #   parameter a is a list of items to sort in non-decreasing order
    #   low = index into a for beginning of which keys to sort
    #   high = index into a for end of which keys to sort
    if low >= high:
        pass  # terminal condition
    else:
        pivotPoint = partition(listToSort, low, high)
        quickSort(listToSort, low, pivotPoint)
        quickSort(listToSort, pivotPoint + 1, high)


def partition(a, low, high):
    global myCount
    #   parameter a is a list of items of size n, that will be partitioned into
    #   either higher or lower than the pivot
    pivotItem = a[low]
    pivotIndex = low
    indexOfKey = pivotIndex + 1

    while indexOfKey <= high:
        myCount += 1
        if a[indexOfKey] < pivotItem:
            pivotIndex += 1
            temp = a[indexOfKey]
            a[indexOfKey] = a[pivotIndex]
            a[pivotIndex] = temp
        indexOfKey += 1

    #  move pivotItem into pivot index, if it isn't already the lowest item
    if pivotIndex != low:
        temp = a[low]
        a[low] = a[pivotIndex]
        a[pivotIndex] = temp
    return pivotIndex

def main():
    ###################################################################################################################
    nTimes = [2,4,8,16,32,64,128,256]  # change here for number of n-values

    #  RANDOM NUMBER FOR DATA
    for x in nTimes:
        nValues1 = []
        nValues2 = []
        for i in range(x):  # note i is index 0 - (x-1)
            temp = random.randint(-128,128)  # range is -128 to 128
            # list/array are pass by ref, need 2 copies, one for each sort
            nValues1.append(temp)  # copy one for mergeSort
            nValues2.append(temp)  # copy two for quickSort
        print("Dataset at n[" + str(x) + "]: " + str(nValues1))

        #  QuickSort evaluation
        t1 = time.perf_counter()
        quickSort(nValues2, 0, x - 1)  # calling quickSort function
        t2 = time.perf_counter()
        timeDifference = t2 - t1
        basicOpsCountQuickSort.append(basicOps())  # append number of operations to list
        runTimesQuickSort.append(timeDifference)  # append run time to list
        estimatedOps = x * (math.log(x, 2))  # this is using the average run time theda (average operations)
        actualOpsPerSec = basicOps() / timeDifference  # actual ops per sec
        estimateRunTime = actualOpsPerSec * estimatedOps
        estimatedTimesQuickSort.append(estimateRunTime)
        reset()  # reset basicOps

        #  MergeSort evaluation
        t1 = time.perf_counter()
        mergeSort(nValues1)  # calling mergeSort function
        t2 = time.perf_counter()
        timeDifference = t2 - t1
        basicOpsCountMergeSort.append(basicOps())  # append number of operations to list
        runTimesMergeSort.append(timeDifference)  # append run time to list
        estimatedOps = x * (math.log(x,2))  # this is using the average run time theda (average operations)
        actualOpsPerSec = basicOps() / timeDifference  # actual ops per sec
        estimateRunTime = actualOpsPerSec * estimatedOps
        estimatedTimesMergeSort.append(estimateRunTime)
        reset()  # reset basicOps

    ###################################################################################################################
    #  GENERATE GRAPHS

    # Graph 1
    plt.subplot(1, 3, 1)  # subplot(nrows, ncols, index, **kwargs)
    plt.plot(nTimes, basicOpsCountMergeSort, color='blue', label="MergeSort")
    plt.plot(nTimes, basicOpsCountQuickSort, color='red', label="QuickSort")
    plt.title('Basic Operations', fontsize=10)
    plt.ylabel("bascicOps")
    plt.xlabel("value (n)")
    plt.legend()  # display legend or key for graph

    # Graph 2  #################################################################################### this is really average ops, not time!!!!!!
    plt.subplot(1, 3, 2)  # subplot(nrows, ncols, index, **kwargs)
    plt.plot(nTimes, runTimesMergeSort, color='blue', label="MergeSort")
    plt.plot(nTimes, runTimesQuickSort, color='red', label="QuickSort")
    plt.title('Actual Run Times', fontsize=10)
    plt.ylabel("time (sec)")
    plt.xlabel("value (n)")
    plt.legend()  # display legend or key for graph

    # Graph 3
    plt.subplot(1, 3, 3)  # subplot(nrows, ncols, index, **kwargs)
    plt.plot(nTimes, estimatedTimesMergeSort, color='blue', label="MergeSort")
    plt.plot(nTimes, estimatedTimesQuickSort, color='red', label="QuickSort")
    plt.title('Estimated Run Times', fontsize=10)
    plt.ylabel("time (sec)")
    plt.xlabel("value (n)")
    plt.legend()  # display legend or key for graph


    plt.suptitle("MergeSort vs QuickSort")
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()  # excucte main function
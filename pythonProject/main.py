"""
    Please implement functions named:  reset, basicOps, mergeSort, merge, bestBasicOps, and worstBasicOps; details follow.

    You don't have to, but you might want to, add a main function and code/test this in your
    favorite Python IDE.
"""

global basicOpCount
# DEBUG global debugCounter

""" reset, resets basic op counter to 0 """


def reset():
    print("--reset--")
    global basicOpCount
    basicOpCount = 0
    # DEBUG global debugCounter
    # DEBUG debugCounter = 0
    return


""" 
    basicOps returns the number of basic operations
    HINT: don't forget to count basic operations!!!
    Would be helpful to DEFINE a basic operation? Otherwise this is an arbitrary node.
"""


def basicOps():
    # DEBUG print("BasicOps: " + str(basicOpCount))
    return basicOpCount


# Just adding to a global variable through function call
def addOp(numToAdd=1):
    global basicOpCount
    basicOpCount += numToAdd
    return  # Garbage Collection?

"""
def addDebug(num):
    global debugCounter
    debugCounter += num
"""

""" 
    mergeSort, implement mergeSort
"""


def mergeSort(a: list) -> list:
    """
    #   parameter 'a' is a list of items to sort in non-decreasing order
    #       non-decreasing means each element will be sorted to be less than or equal to the next element.
    #   mergeSort (a Divide and Conquer) algorithm:
    #       terminal condition is when len(items), aka n, is 1.  A list of 1 item is properly sorted!
    #
    #       otherwise:
    #           m (middle element)  equals the floor of n/2, hint the integer division operator in Python is //
    """
    n = len(a)
    # DEBUG print("mergeSort called on a of size [" + str(n) + "]\n")
    if n < 1:
        return a
    if n == 1:
        return a
    m = n // 2
    b = list()
    c = list()

    b.extend(a[0:m])  # copy first m elements, items[0..m-1] from items into a new list b[0..m-1]
    # DEBUG print("b " + str(b))
    c.extend(a[m:n])  # copy remaining elements from items[m..n-1] into a new list c[0..n-1-m]
    # DEBUG print("c " + str(c))
    b = mergeSort(b)
    c = mergeSort(c)

    # DEBUG print("calling merge called on 'a' of size [" + str(len(a)) + "]\n")
    a = merge(a, b, c)  # Sorted version of what was described.
    return a


""" 
    merge, merges the sorted lists b and c into a.
"""


def merge(a, b, c):
    # DEBUG print("merge on a of size " + str(len(a)) + "\nb of size " + str(len(b)) + "\nc of size " + str(len(c)))
    # DEBUG if (len(b) + len(c)) != len(a):
    # DEBUG     print("Error in merge, length of b and c do not match a")
    # DEBUG     return a
    """
    # parameter 'a' is a list of items of size n, where n = len(b) + len(c), that will contain
    #   sorted items from b and c in non-decreasing order
    #   parameter b is first half of list a sorted in non-decreasing order
    #   parameter c is second half of list a sorted in non-decreasing order
    """
    #   merge:
    n = len(a)  # n (length of a)
    m = n // 2  # m (middle element) equals the floor of n/2, hint the integer division operator in Python is //
    # Iterator ints to keep track of indexes in each list.
    i = 0  # i is the current index of a (where to insert next sorted item), initially i == 0
    j = 0  # j is the current index of b (where to get value used for key comparison), initially j == 0
    k = 0  # k is the current index of c (where to get value used for key comparison), initially k == 0
    # To determine which size is bigger, if called on uneven b and c:
    size_b = len(b)
    size_c = len(c)

    #       // assign smaller of next item in 'b' or next item in 'c' into the next item in 'a'
    while (j < n - k) and (k < n - j) and (j < size_b and k < size_c):  # while j < m and k < n - m
        if b[j] <= c[k]:
            a[i] = b[j]
            j += 1
        else:
            a[i] = c[k]
            k += 1
        i += 1
        addOp()

    #       // If any values remain in b or c, implies that the remaining items
    #       // are larger than the last item inserted into the merged list (a).
    #       // Therefore, append any remaining items
    #       // also, exactly one case is true, since we don't compare the last item to itself either
    # DEBUG else:
    # DEBUG     print("merge:\nsize of a [" + str(n) + "]\nsize of b [" + str(j) + "]\nsize of c [" + str(k) + "]")
    if j < size_b:
        a[i:n] = b[j:size_b]
        # DEBUG print("size of b [" + str(j) + "]")
    else:
        a[i:n] = c[k:size_c]
        # DEBUG print("size of c [" + str(k) + "]")
    """
    # DEBUG print(str(a))
    # DEBUG print("merge done")

    if basicOps() < bestBasicOps(n):
        print("error with basic op counting less")

    elif basicOps() > worstBasicOps(n):
        print("error with basic op counting more")

    else:
        print("correct enough op count")
"""
    return a


""" 
    bestBasicOps, for a list the size of n, where n is a power of 2 (n = 2^k), this function 
    returns b(n), aka the best case or minimal number of key comparisons, as a double

    best case of merge sort only does n/2 key comparisons because either b[m-1] < c[0] or b[0] < c[n-1-m]

    therefore, for bestBasicOps, assume that the recurrence relation is:
        b(1) = 0
        for n>1, n a power of 2 is:  b(n) = 2*b(n/2) + n/2 

    Hint: starting with given b(1), calculate b(2), b(4), etc. until you find a pattern.
    Using the pattern, find a closed form solution.  Then use induction to prove it's true
    implement here the candidate solution
"""


def bestBasicOps(n):
    ans = 0.0
    if n > 1:  # Otherwise default 'ans'
        ans = 2 * bestBasicOps(n / 2) + n / 2  # The formula provided is recursive.
    # DEBUG print("bestBasicOps call on List of size " + str(n) + " returns " + str(ans) + "\n")
    return ans


""" 
    worstBasicOps, for a list the size of n, where n is a power of 2 (n = 2^k), this function 
    returns w(n), aka the worst case or maximum number of key comparisons, as a double

    worst case of merge sort does n-1 key comparisons because there's no need to compare the last element to itself

    therefore, for worstBasicOps, assume that the recurrence relation is:
        w(1) = 0
        for n>1, n a power of 2 is:  w(n) = 2*w(n/2) + n - 1 

    Hint: starting with given w(1), calculate w(2), w(4), etc. until you find a pattern
    from this pattern, find a closed form solution.  Then use induction to prove it's true
    implement here the candidate solution

"""


def worstBasicOps(n):
    ans = 0.0
    if n > 1:
        ans = 2 * worstBasicOps(n / 2) + n - 1
    # DEBUG print("worstBasicOps call on List of size " + str(n) + " returns " + str(ans) + "\n")
    return ans

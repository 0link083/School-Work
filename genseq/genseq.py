import matplotlib.pyplot as plt
import math
import random
import time

memoizationCache = {}
counter = 0
s1 = ""
s2 = ""


def basicOps():
    global counter
    return counter


def setS1(seq):
    global s1
    s1 = seq


def setS2(seq):
    global s2
    s2 = seq


def resetAll():
    global counter
    global s1
    global s2
    global memoizationCache
    counter = 0
    s1 = ""
    s2 = ""
    memoizationCache = {}


def resetCount():
    global counter
    counter = 0


#######################################################################################################################
# D&C NO Cache (NOT MEMO)

def genSeqDC(i, j):
    global s1
    global s2
    global counter

    counter += 1

    # Note the unit tests assume that i and j are zero-based!
    # For example given the strings in the slides ("ACGCTGA", "ACTGT"), the unit tests invoke genSeqDC(len(s1)-1, len(s2)-1)
    # or more specifically, for this example, it calculates genSeqDC(6, 4)  *** NOT genSeqDC(7,4) ***

    match = -3
    subst = 1
    indel = 5

    left = 0
    up = 0
    diag = 0
    dist = subst

    if (s1[i] == s2[j]):
        dist = match

    if (i == 0):
        if (j == 0):
            return dist

        else:
            left = genSeqDC(i, j - 1) + indel
            up = indel * (j + 2)
            diag = indel * j + dist
    elif j == 0:
        left = indel * (i + 2)
        up = genSeqDC(i - 1, j) + indel
        diag = indel * i + dist
    else:
        left = genSeqDC(i, j - 1) + indel
        up = genSeqDC(i - 1, j) + indel
        diag = genSeqDC(i - 1, j - 1) + dist

    return min(left, up, diag)


def DCtimeComplexity(m, n):
    # k = 0
    # if m > n:
    #    k = m
    # else:
    #    k = n
    # return ((3**(k+1)) - 3) / 2

    s = [[0 for i in range(n)] for j in range(m)]
    for i in range(m):
        for j in range(n):
            if i == 0:
                s[i][j] = 3 * (j + 1)
            elif j == 0:
                s[i][j] = 3 * (i + 1)
            else:
                s[i][j] = 3 + s[i - 1][j - 1] + s[i - 1][j] + s[i][j - 1]
    return s[m - 1][n - 1]


#######################################################################################################################
# D&C with Cache (MEMO)

def memoGenSeqDC(i, j):
    global s1
    global s2
    global counter
    global memoizationCache

    if (str(j) + ',' + str(i) in memoizationCache):
        return memoizationCache[str(j) + ',' + str(i)]

    else:
        match = -3
        subst = 1
        indel = 5

        left = 0
        up = 0
        diag = 0
        dist = subst

        counter += 1

        if (s1[i] == s2[j]):
            dist = match

        if (i == 0):  # we are on the edge
            if (j == 0):  # we are on the other edge
                return dist
            else:
                left = memoGenSeqDC(i, j - 1) + indel
                up = indel * (j + 2)
                diag = indel * j + dist

        elif j == 0:
            left = indel * (i + 2)
            up = memoGenSeqDC(i - 1, j) + indel
            diag = indel * i + dist
        else:
            left = memoGenSeqDC(i, j - 1) + indel
            up = memoGenSeqDC(i - 1, j) + indel
            diag = memoGenSeqDC(i - 1, j - 1) + dist

        memoizationCache[str(j) + ',' + str(i)] = min(left, up, diag)
        return min(left, up, diag)


#######################################################################################################################
# D&C with Cache (MEMO)
def geneSeqDP(s1, s2):
    global counter
    # m is length of string 1, i is offset into m (the row #)
    m = len(s1)
    counter += m
    # n is length of string 2, j is offest into n (the column #)
    n = len(s2)
    counter += n
    # allocate and zero-full an array s of size (m + 1) x (n + 1) // +1 to initialize first rows and columns indel values
    s = [[0 for x in range(n + 1)] for x in range(m + 1)]

    for i in range(1, m + 1):
        s[i][0] = i * 5
    # initialize columns
    # for j in 1...n+1:  S[0][j] = j*indel
    for j in range(1, n + 1):
        s[0][j] = j * 5

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            counter += 1
            dist = 0
            if s1[i - 1] == s2[j - 1]:
                dist = -3
            else:
                dist = 1
            temp1 = s[i - 1][j - 1] + dist
            temp2 = s[i - 1][j] + 5
            temp3 = s[i][j - 1] + 5
            # find smallest temp value, it is the value we store
            keep = 0
            if temp1 < temp2:
                keep = temp1
            else:
                keep = temp2
            if keep < temp3:
                keep = keep
            else:
                keep = temp3
            s[i][j] = keep

    return s[m][n]


def DPtimeComplexity(m, n):
    return (m+1)*(n+1)-1  # == (m+1)*(n+1)-1


def main():
    ###################################################################################################################

    kTimes = 250
    geneAlphabet = ['A', 'C', 'G', 'T']
    basicOpsCountDP = []
    runTimesDP = []
    estimatedTimesDP = []
    basicOpsCountDCMemo = []
    runTimesDCMemo = []
    estimatedTimesDCMemo = []
    estimatedOpsDP = []
    estimatedOpsDCMemo = []
    basicOpsCountDC = []
    runTimesDC = []

    for k in range(kTimes):
        resetAll()
        m = ''
        n = ''
        # Create m and n (stings using A,C,G,T for Gene Sequence)
        for i in range(random.randint(2, 10)):  # possible limit (upper) for D&C is 2^7 = 128
            temp = random.randint(0, 3)  # range of alphabet
            m += geneAlphabet[temp]
        for i in range(random.randint(2, 10)):  # possible limit (upper) for D&C is 2^7 = 128
            temp = random.randint(0, 3)  # range of alphabet
            n += geneAlphabet[temp]

        x = len(n)
        y = len(m)
        setS1(n)
        setS2(m)

        #  DP evaluation
        t1 = time.perf_counter()
        geneSeqDP(n, m)  # calling DP function
        t2 = time.perf_counter()
        timeDifference = t2 - t1
        basicOpsCountDP.append(basicOps())  # append number of operations to list
        runTimesDP.append(timeDifference)  # append run time to list
        estimatedOps = DPtimeComplexity(x, y)  # this is using the average run time
        estimatedOpsDP.append(estimatedOps)
        actualOpsPerSec = basicOps() / timeDifference  # actual ops per sec
        estimateRunTime = actualOpsPerSec * estimatedOps
        estimatedTimesDP.append(estimateRunTime)
        resetCount()  # reset basicOps

        #  D&C Memo evaluation
        t1 = time.perf_counter()
        memoGenSeqDC(x - 1, y - 1)  # calling D&C Memo function
        t2 = time.perf_counter()
        timeDifference = t2 - t1
        basicOpsCountDCMemo.append(basicOps())  # append number of operations to list
        runTimesDCMemo.append(timeDifference)  # append run time to list
        estimatedOps = basicOps()  # this is using the average run time
        estimatedOpsDCMemo.append(estimatedOps)
        actualOpsPerSec = basicOps() / timeDifference  # actual ops per sec
        estimateRunTime = actualOpsPerSec * estimatedOps
        estimatedTimesDCMemo.append(estimateRunTime)
        resetCount()  # reset basicOps

        #  D&C evaluation
        t1 = time.perf_counter()
        genSeqDC(x - 1, y - 1)  # calling D&C function
        t2 = time.perf_counter()
        timeDifference = t2 - t1
        basicOpsCountDC.append(DCtimeComplexity(x, y))  # append number of operations to list
        runTimesDC.append(timeDifference)  # append run time to list
        resetCount()  # reset basicOps

    # Graph 1
    plt.subplot(2, 2, 1)  # subplot(nrows, ncols, index, **kwargs)
    plt.scatter(estimatedTimesDP, basicOpsCountDP, color='blue', label="DP Algorithm")
    plt.scatter(estimatedTimesDCMemo, basicOpsCountDCMemo, color='red', label="D&C Memo (cache)")
    plt.title('Estimated run-time', fontsize=10)
    plt.ylabel("bascicOps")
    plt.xlabel("time (sec)")
    plt.legend()  # display legend or key for graph

    # Graph 2
    plt.subplot(2, 2, 2)  # subplot(nrows, ncols, index, **kwargs)
    plt.scatter(runTimesDP, basicOpsCountDP, color='blue', label="DP Algorithm")
    plt.scatter(runTimesDCMemo, basicOpsCountDCMemo, color='red', label="D&C Memo (cache)")
    plt.title('Actual Run Times', fontsize=10)
    plt.ylabel("basicOps")
    plt.xlabel("time (sec)")
    plt.legend()  # display legend or key for graph

    # Graph 3
    plt.subplot(2, 2, 3)  # subplot(nrows, ncols, index, **kwargs)
    plt.scatter(runTimesDP, estimatedOpsDP, color='blue', label="DP Algorithm")
    plt.scatter(runTimesDCMemo, estimatedOpsDCMemo, color='red', label="D&C Memo (cache)")
    plt.title('Estimated Ops', fontsize=10)
    plt.ylabel("Estimated-Ops")
    plt.xlabel("time (sec)")
    plt.legend()  # display legend or key for graph

    # Graph 4
    plt.subplot(2, 2, 4)  # subplot(nrows, ncols, index, **kwargs)
    plt.scatter(runTimesDC, basicOpsCountDC, color='green', label="D&C (NO CACHE)")
    plt.scatter(runTimesDCMemo, basicOpsCountDCMemo, color='red', label="D&C Memo (cache)")
    plt.title('Estimated run-time', fontsize=10)
    plt.ylabel("basicOps")
    plt.xlabel("time (sec)")
    plt.legend()  # display legend or key for graph
    plt.suptitle("DP vs D&C vs D&C Memo (Gene Sequence)")
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()  # execute main function

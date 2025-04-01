import math

import numpy as np

"""
    Implement RSA Encryption, call your method names, details below:
    sieve(), gcd_ex(a, b), modulo_expo(base, exponent, modulus), 
"""

# zero-fill sieves it's generally faster than one-filling
#     value of zero in the array implies that the current index is a prime number
#     value of one in the array implies that the current index is a composite number
sieves = np.zeros(shape=2 ** 17, dtype=np.uint32)
primes = sieves  # fill primes array with prime #s calculated by sieve

# init prime number list for unit tests

""" 
    using the Sieve of Eratosthenes, please calculate prime numbers < 2^17
    For this assignment only use prime numbers > 2^16, which is a little less than half the prime numbers)
"""


def sieve():
    global primes
    global sieves

    primes = sieves % primes


"""
Please see Canvas | Files | Lecture Notes | 'CS3310Lect07-08a_Euclid, Fibonacci, Binet, and Lamé, The first recorded
complexity analysis of an algorithm.' Note: the ***basic*** Euclidean Algorithm only returns the gcd, but your code needs to use
the ***Extended*** Euclidian Algorithm's and return the tuple(gcd, s, and t)

Like the aforementioned document mentions, in section 5.g, the efficiency of the Extended Euclidian algorithm
is big-Theta of (lg n). Since lg n is very efficient, it's okay to calculate the Extended Euclidian Algorithm using D&C (recursively).
However, you can also calculate it iteratively, which has the same time complexity as the D&C does, 
but will be an order of magnitude faster than D&C.

The zybook (see see https://learn.zybooks.com/zybook/UVUCS3310MortensenSpring2021/chapter/9/section/5) 
doesn't do a very good job of clearly defining how to calculate the extended GCD. 
Therefore, please see https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm 
for the pseudo-code of the Extended Euclidian Algorithm.
"""


def gcd_ex(a, b):
    return math.gcd(a,b)



""" 
implement modular exponentiation
https://learn.zybooks.com/zybook/UVUCS3310MortensenSpring2021/chapter/9/section/7
See Figure 9.7.4: An iterative algorithm for fast modular exponentiation.
"""


def modulo_expo(base, exponent, modulus):
    pass


"""
modulo_number used to calculate d and e will be (p-1)*(q-1)
function should return d, e; function should use extended euclidian algorithm
"""


def get_keys(p, q):
    gcd_ex(p, q)


"""
c = (m ** e) % n (return c)
where c is the encrypted message (m allowable up to max of a 32 bit unsigned integer, 2^32-1)
"""


def encrypt(m, e, n):
    return (m ** e) % n


"""
m = (c ** d) % n (return m)
where m is the decrypted plain text message (up to 32 bit unsigned integer)
"""


def decrypt(c, d, n):
    return (c ** d) % n

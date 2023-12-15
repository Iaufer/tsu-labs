#Алгоритм Баррета
import time
import math
import random

def alg_barret(x, m, b, k, r1, r2):
    

    if b > 3:

        # _q = ((x // b**(k-1)) * z) // b**(k+1)
        # r1 = x % b**(k+1)
        # r2 = (_q * m) % b**(k+1)

        if r1 >= r2:
            _r = r1 - r2
        else:
            _r = b**(k+1) + r1 - r2

        while (_r >= m):
            _r = _r - m
    else:
        print("Число b слишком маленькое!")
    return _r

def standart(x,m):
    while x >= m:
        x-=m
    #z = x%m
    return x

def test(x, m):


    start = time.time_ns()
    res = x % m
    #res = standart(x, m)
    #print(res)
    
    print("Время работы %: ", round(time.time_ns() - start, 5))  
    
    b = 10
    k = len(str(m))
    n = len(str(m))
    z = (b**(2*k)) // m
    _q = ((x // b**(k-1)) * z) // b**(k+1)
    r1 = x % b**(k+1)
    r2 = (_q * m) % b**(k+1)
    start = time.time_ns()
    res = alg_barret(x, m, b, k, r1, r2)
    #print(res)
    print("Время работы Алгоритма Баррета: ", round(time.time_ns() - start))


    # start = time.time_ns()
    # res = standart(x, m)
    # print("Время работы вычетания: ", round(time.time_ns() - start))  


    print(alg_barret(x, m, b, k, r1, r2) == x % m)
    print(alg_barret(x, m, b, k, r1, r2))
    print(x % m)


if __name__ == '__main__':
    
    x = 218378463287
    m = 16   

    test(x, m)
#Метод Гордона
#from Crypto.Util.number import getPrime
from sympy import isprime, randprime
import random
def gordon():
    
    #s = getPrime(90)
    # = getPrime(90)

    s = randprime(10 ** 250, 10 ** 300)
    t = randprime(10 ** 250, 10 ** 300)

    i = random.randint(1, 100)
    r = 2 * i * t + 1

    while not isprime(r):
        i += 1
        r = 2 * i * t + 1
    
    p0 = 2 * (pow(s, r - 2, r)) * s - 1
    j = random.randint(1, 100)
    p = 2 * j * r * s + p0

    while not isprime(p):
        j += 1
        p = 2 * j * r * s + p0
    
    return p
    

print(gordon())
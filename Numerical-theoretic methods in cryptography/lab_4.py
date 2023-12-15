import random
from sympy.ntheory.factor_ import totient


#Функция Эйлера
def error_f(n,t):
    return float((totient(n)/n))**t

#Тест Ферма
def ferma_test(n, t):
    while t:
        a = random.randint(2, n - 2)
        r = pow(a, n - 1, n)
        t -= 1
    if r != 1:  
        print("Число 100% составное!")
        return
    
    print("Число простое!")


# 436579856702186532875472738154672 - составное число
# 6099126388594931945520833493722385030733 - простое
# 75361 - число карлм t = 1 and t = 15 and 62745
n = 62745
t = 1

ferma_test(n, t)
print("Вероятность ошибки = ", error_f(n, t))


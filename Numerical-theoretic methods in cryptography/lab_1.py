# 1. Быстрое возведение в квадрат.
import time

def fast_squaring(n):
    k = len(n)
    x = [int(i) for i in n] # число в список его цифр
    x.reverse() # перевернутый список
    y = [0 for i in range (2 * k)] # 1. пустой список y

    for i in range(k): # 2
        uv = y[2 * i] + x[i] * x[i] # 2.1
        c = 0
        u = uv // 10
        v = uv % 10
        y[2 * i] = v
        for j in range(i + 1, k): # 2.2
            cuv = y[i + j] + 2 * x[i] * x[j] + c*10 + u
            c = cuv // 100
            v = cuv % 10
            u = (cuv - c * 100) // 10
            y[i + j] = v
        if c != 0: # 2.3
            y[i + k + 1] += c #c
        y[i + k] += u
    
    return int(''.join([str(i) for i in reversed(y)]))


#n = input('Введите число: ')
n = "234324234839255643298762343242348392556432987623432423483925564329876"

start = time.time_ns()
res_1 = fast_squaring(n)
print("Время работы быстрого возведения в квадрат: ", (time.time_ns() - start) )


start = time.time_ns()
res_2 = pow(int(n), 2)
print("Время работы функции: ", (time.time_ns() - start))

start = time.time_ns()
res_3 = int(n) * int(n)
print("Время работы умножения: ", (time.time_ns() - start))

print(res_1)
print(res_2)
print(res_3)
print(res_1 == res_2 == res_3)

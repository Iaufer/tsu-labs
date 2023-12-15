#Дихотомический алгоритм возведения в степень
import time
import random
#справа налево
def alg_RL(x, y):
    q = x
    z = x
    for i in range(y.bit_length() - 2, -1, -1):
        q = q ** 2
        if (y >> i) & 1:
            z = z * q

    return z



#слева направо


def alg_LR(x, y):#справа налево
    z = x
    for i in range(y.bit_length() - 2, -1, -1):
        z = z ** 2
        if (y >> i) & 1:
            z *= x #вот тут разница  
    return z


def standart_pow(x, y):
    while y:
        x *= x
        y -= 1
    return x


# x = random.randint(1000000, 9999999999999)
# y = random.randint(100, 999)
# print(x)
# print(y)

x = 3842016574386574386532795843865542838497538590873492358423593439355538
y = 100



start = time.time_ns()
res_1 = alg_LR(x, y)
print("Время работы Дихотомического алгоритма возведения в степень: ", (time.time_ns() - start))


start = time.time_ns()
res_2 = pow(x, y)
#result_2 = standart_pow(x, y)
print("Время работы стандартной функции: ", time.time_ns() - start)

start = time.time_ns()
#result_2 = pow(x, y)
res_3 = standart_pow(x, y)
print("Время работы умножения: ", time.time_ns() - start)





# #слева направо
# print(alg_LR(x, y))
# print(x ** y)
print(alg_LR(x, y) == x ** y == pow(x, y))








#if(y >> y.bit_length() - 1) == 0:
# print(bin(y >> 3), y ,y.bit_length())
# print((y >> (y.bit_length() - 1)))






# print(alg_RL(x, y))
# print("---------")
# print(x ** y)
# print(alg_RL(x, y) == x ** y)
# print(y.bit_length())
# print(bin(y))



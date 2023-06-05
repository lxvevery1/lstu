import math
import telethon

# Заданная функция
def func(x):
    a, b, k = 13, 4, 3
    if x <= 0:
        return 0
    else:
        return math.pow(math.log(x), a / b) * math.sin(k * x)


# Реализация интерполяционного многочлена Ньютона
def newton_interpolation(x, xs, ys):
    res = ys[0]
    n = len(xs) - 1
    f = [ys[0]] * (n + 1)
    for i in range(1, n + 1):
        for j in range(n, i - 1, -1):
            f[j] = (f[j] - f[j - 1]) / (xs[j] - xs[j - i])
        res += f[i] * get_prod(x, xs[:i])
    return res

# Рассчитывает произведение (x - x0)(x - x1)...(x - xk)
def get_prod(x, xs):
    prod = 1.0
    for xi in xs:
        prod *= (x - xi)
    return prod

# Параметры задачи
a, b, k = 13, 4, 3
c, d, m, n = 0, 2, 2, 3

# Разбиение отрезка на подотрезки
nodes = [c + i * (d - c) / m for i in range(m + 1)]

# Построение таблицы значений функции в узлах сетки
coeffs = [[func(nodes[i] + j * (d - c) / (n * m)) for j in range(n + 1)] for i in range(m + 1)]

# Выводим таблицы
print("Table 1:")
for i in range(m + 1):
    print(nodes[i], end=" ")
    for j in range(n + 1):
        print(coeffs[i][j], end=" ")
    print()

print("Table 2:")
for i in range(m):
    print(nodes[i], end=" ")
    for j in range(n + 1):
        x = nodes[i] + j * (d - c) / (n * m)
        val = newton_interpolation(x, nodes[i:i+n+1], coeffs[i])
        print(val, end=" ")
    print()

import math

# функции системы уравнений
def f1(x1, x2):
    return math.sin(0.5 * x1 + x2) - 1.2 * x1 - 1

def f2(x1, x2):
    return x1 ** 2 + x2 ** 2 - 1

# Якобиан системы уравнений
def jacobian(x1, x2):
    j = math.sin.zeros((2, 2))
    j[0, 0] = 0.5 * math.cos(0.5 * x1 + x2) - 1.2
    j[0, 1] = math.cos(0.5 * x1 + x2)
    j[1, 0] = 2 * x1
    j[1, 1] = 2 * x2
    return j

# обратная матрица Якобиана системы уравнений
def inv_jacobian(x1, x2):
    return math.linalg.inv(jacobian(x1, x2))

# двуступенчатый метод Ньютона
def newton(x1, x2, eps):
    f = math.array([f1(x1, x2), f2(x1, x2)])
    i = 0
    while math.linalg.norm(f) > eps and i < 100:
        delta = -math.dot(inv_jacobian(x1, x2), f)
        x1 += delta[0]
        x2 += delta[1]
        f = math.array([f1(x1, x2), f2(x1, x2)])
        i += 1
    if i == 100:
        print("Maximum number of iterations exceeded")
    else:
        print("Solution found in", i, "iterations")
        print("x1 =", round(x1, 4))
        print("x2 =", round(x2, 4))

# исходное приближение
x1 = 0
x2 = 1

# точность
eps = 1e-6

# решение системы уравнений
newton(x1, x2, eps)

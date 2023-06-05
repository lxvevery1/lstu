import math

def f(x):
    return 0.5*math.exp(-math.sqrt(x)) - 0.2*math.sqrt(x**3) + 2

def dichotomy(a, b, eps):
    while b - a >= eps:
        c = (a + b) / 2
        if f(a) * f(c) < 0:
            b = c
        else:
            a = c
    return (a + b) / 2

root = dichotomy(0, 10, 1e-6)
print(root)
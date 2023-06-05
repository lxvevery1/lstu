import math

def f1(x1, x2):
    return math.sin(0.5 * x1 + x2) - 1.2 * x1 - 1

def f2(x1, x2):
    return x1**2 + x2**2 - 1

def F(x1, x2):
    return f1(x1, x2)**2 + f2(x1, x2)**2

def grad_F(x1, x2):
    df1_dx1 = 2 * (math.sin(0.5 * x1 + x2) - 1.2 * x1 - 1) * (0.5 * math.cos(0.5 * x1 + x2) - 1.2) + 4 * x1 * (x1**2 + x2**2 - 1)
    df1_dx2 = 2 * (math.sin(0.5 * x1 + x2) - 1.2 * x1 - 1) * math.cos(0.5 * x1 + x2) + 4 * x2 * (x1**2 + x2**2 - 1)
    return [df1_dx1, df1_dx2]

def gradient_descent(alpha, eps):
    x1, x2 = 1, 1  # starting point
    tick = 0
    while True:
        grad = grad_F(x1, x2)
        if math.sqrt(grad[0]**2 + grad[1]**2) < eps & tick == 100:
            return (x1, x2)
        x1 -= alpha * grad[0]
        x2 -= alpha * grad[1]
        tick+=1

x1, x2 = gradient_descent(0.3, 1e-6)
print("Корни системы уравнений: x1 = {:.6f}, x2 = {:.6f}".format(x1, x2))

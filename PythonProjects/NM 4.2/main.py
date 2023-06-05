import math

def f(x1, x2):
    return math.pow(math.sin(0.5 * x1 + x2) - 1.2 * x1 - 1, 2) + math.pow(x1, 2) + math.pow(x2, 2) - 1

def grad_f(x1, x2):
    df_dx1 = 2 * (math.sin(0.5 * x1 + x2) - 1.2 * x1 - 1) * (0.5 * math.cos(0.5 * x1 + x2) - 1.2) + 2 * x1
def grad_f(x1, x2):
    df_dx1 = 2 * (math.sin(0.5 * x1 + x2) - 1.2 * x1 - 1) * (0.5 * math.cos(0.5 * x1 + x2) - 1.2) + 2 * x1
    df_dx2 = 2 * (math.sin(0.5 * x1 + x2) - 1.2 * x1 - 1) * math.cos(0.5 * x1 + x2) + 2 * x2
return [df_dx1, df_dx2]

def gradient_descent(alpha, threshold):
x1 = 0
x2 = 0
while True:
grad = grad_f(x1, x2)
x1_new = x1 - alpha * grad[0]
x2_new = x2 - alpha * grad[1]
if abs(x1_new - x1) < threshold and abs(x2_new - x2) < threshold:
break
x1 = x1_new
x2 = x2_new
return [x1, x2]

alpha = 0.3
threshold = 0.0001
result = gradient_descent(alpha, threshold)
print("x1 =", result[0])
print("x2 =", result[1])
print("f(x1, x2) =", f(result[0], result[1]))
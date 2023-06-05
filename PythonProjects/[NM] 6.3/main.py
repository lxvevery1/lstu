import math
import cmath

import sympy as sp
import matplotlib.pyplot as plt


def plot_complex_values_dots(real_values, imag_values):
    plt.scatter(real_values, imag_values)
    plt.xlabel('Real')
    plt.ylabel('Imaginary')
    plt.grid(True)
    plt.show()

def plot_complex_values_lines(x, y):
    plt.figure(figsize=(8, 6))
    plt.plot(x, y)
    plt.xlabel('Real')
    plt.ylabel('Imaginary')
    plt.title('Complex Values')
    plt.grid(True)
    plt.show()


# region Known values: E1m, E2m, Ikm, w, freq, R, L, C

E1m = 90
E2m = 50
Ikm = 9

w1 = math.degrees(-70)
w2 = math.degrees(45)
w3 = math.degrees(-50)

freq = 50

R1 = 11
R2 = 5
R3 = 10
R4 = 7

L1 = 35 * 10 ** -3
L2 = 70 * 10 ** -3
L3 = 200 * 10 ** -3

C1 = 100 * 10 ** -6
C2 = 70 * 10 ** -6
C3 = 200 * 10 ** -6

# endregion


# region XC, XL, jXC, jXL

XC1 = 1 / (2 * 3.14 * freq * C1)
XC2 = 1 / (2 * 3.14 * freq * C2)
XC3 = 1 / (2 * 3.14 * freq * C3)

XL1 = 2 * 3.14 * freq * L1
XL2 = 2 * 3.14 * freq * L2
XL3 = 2 * 3.14 * freq * L3

jXC1 = XC1 * 1j
jXC2 = XC2 * 1j
jXC3 = XC3 * 1j

jXL1 = XL1 * 1j
jXL2 = XL2 * 1j
jXL3 = XL3 * 1j

print("jXC1 =", jXC1)
print("jXC2 =", jXC2)
print("jXC3 =", jXC3)

print("jXL1 =", jXL1)
print("jXL2 =", jXL2)
print("jXL3 =", jXL3, "\n")

# endregion


# region E1, E2, I6_IK

E1 = E1m / (math.sqrt(2)) * (cmath.cos(w1) + 1j * cmath.sin(w1))
E2 = E2m / (math.sqrt(2)) * (cmath.cos(w2) + 1j * cmath.sin(w2))
I6_IK = Ikm / (math.sqrt(2)) * (cmath.cos(w3) + 1j * cmath.sin(w3))

print("E1 =", E1)
print("E2 =", E2)
print("I6_IK =", I6_IK, "\n")

# endregion


# region I

# Define symbolic variables I
I1, I2, I3, I4, I5, t = sp.symbols('I1 I2 I3 I4 I5 t', complex=True)

# Define equations for I
eq1 = I3 - I1 - I4
eq2 = I6_IK - I2 + I1
eq3 = I2 + I5 - I3
eq4 = I2 * (jXL1 + R1 - jXC1) + I3 * (R3 + jXL3) - E1
eq5 = I5 * (jXL2 - jXC2) + I3 * (R3 + jXL3) + I4 * (-jXC3 + R4) - E2

# Solve the system of equations
solution_I = sp.solve((eq1, eq2, eq3, eq4, eq5), (I1, I2, I3, I4, I5))

# Retrieve the values
I1 = solution_I[I1]
I2 = solution_I[I2]
I3 = solution_I[I3]
I4 = solution_I[I4]
I5 = solution_I[I5]

print(
    "eq1 = I3 - I1 - I4 \neq2 = I6_IK - I2 + I1 \neq3 = I2 + I5 - I3 \neq4 = I2 * (jXL1 + R1 - jXC1) + I3 * (R3 + "
    "jXL3) - E1 \neq5 = I5 * (jXL2 - jXC2) + I3 * (R3 + jXL3) + I4 * (-jXC3 + R4) - E2\n")
print("I1 =", I1)
print("I2 =", I2)
print("I3 =", I3)
print("I4 =", I4)
print("I5 =", I5)
print("I6_IK =", I6_IK)

# endregion


# region i_t

# Define the currents and their corresponding variables
I__i_t = [(I1, 'i1_t'), (I2, 'i2_t'), (I3, 'i3_t'), (I4, 'i4_t'), (I5, 'i5_t'), (I6_IK, 'i6_t')]

# Compute and print the in_t
for In, in_t in I__i_t:
    i_t_expr = math.sqrt(2) * abs(In) * sp.sin(50 * t + sp.atan(sp.im(In) / sp.re(In)))
    print(f"{in_t} =", i_t_expr)
print()

# endregion


# region f

f1 = 0
f2 = f1 + E1

f6 = sp.expand(f2 - I2 * jXL1)
f7 = sp.expand(f6 - I2 * R1)
f3 = sp.expand(f7 - I2 * -jXC1)
f8 = sp.expand(f3 - I3 * R3)
f9 = sp.expand(f1 - I4 * -jXC3)
f4 = f9 - I4 * R4
f5 = f4 - I6_IK * R2
f10 = sp.expand(f4 - I5 * jXL2)
f11 = sp.expand(f10 + E2)

print("f1 =", f1)
print("f2 =", f2)
print("f3 =", f3)
print("f4 =", f4)
print("f5 =", f5)
print("f6 =", f6)
print("f7 =", f7)
print("f8 =", f8)
print("f9 =", f9)
print("f10 =", f10)
print("f11 =", f11, "\n")

# endregion


# region I_conj

# Checking the energy balance of capacities
print("Let's find the conjugate complexes of currents:")
I1_conj = sp.conjugate(I1)
I2_conj = sp.conjugate(I2)
I3_conj = sp.conjugate(I3)
I4_conj = sp.conjugate(I4)
I5_conj = sp.conjugate(I5)
I6_IK_conj = sp.conjugate(I6_IK)

print("I1_conjugate =", I1_conj)
print("I2_conjugate =", I2_conj)
print("I3_conjugate =", I3_conj)
print("I4_conjugate =", I4_conj)
print("I5_conjugate =", I5_conj)
print("I6_IK_conjugate =", I6_IK_conj, "\n")

# endregion


U6_IK = sp.expand(I4 * (R4 - jXC3) + I6_IK * R2 + E1)

print("U6_Ik = ", U6_IK)
print("Ф2 - Ф5 = ", f2 - f5)
print("Ф5 = U6_IK - Ф2 =", U6_IK - f2, '\n')


# region Sum of capacities

# Let's find the capacity of the energy sources:
Se1 = sp.expand(E1 * I1_conj)
Se2 = sp.expand(E2 * I5_conj)
Sik = sp.expand(U6_IK * I6_IK_conj)

print("Se1 =", Se1)
print("Se2 =", Se2)
print("Sik =", Sik, "\n")

# Let's find the power consumption of the circuit:
S12 = sp.expand((I2 * I2_conj * 0))
S13 = sp.expand(I3 * I3_conj * (jXL3 + R3))
S14 = sp.expand((I4 * I4_conj * (-jXC3 + R4)))
S23 = sp.expand((I2 * I2_conj * (jXL1 - jXC1 + R1)))
S24 = sp.expand((I6_IK * I6_IK_conj * R2))
S34 = sp.expand((I5 * I5_conj * (jXL2 - jXC2)))

print("S12 =", f"{I2} * {I2_conj} * {0}", '=\t', S12)
print("S13 =", f"{I3} * {I3_conj} * ({jXL3} + {R3})", '=\t', S13)
print("S14 =", f"{I4} * {I4_conj} * ({-jXC3} + {R4})", '=\t', S14)
print("S23 =", f"({I2} * {I2_conj} * ({jXL1} - {jXC1} + {R1})", '=\t', S23)
print("S24 =", f"({I6_IK} * {I6_IK_conj} * {R2})", '=\t', S24)
print("S34 =", f"{I5} * {I5_conj} * ({jXL2} - {jXC2})", '=\t', S34, "\n")

# Let's find the sum of the capacities:
S_source = Se1 + Se2 + Sik
S_circuit = sp.expand(S12 + S13 + S14 + S23 + S24 + S34)

print("S_source =", f"{Se1} + {Se2} + {Sik}", '=\t', S_source)
print("S_circuit =", f"{S12} + {S13} + {S14} + {S23} + {S24} + {S34}", '=\t', S_circuit, "\n")

# Lets find an error
S_error_real = (abs(sp.re(S_source) - sp.re(S_circuit)) / abs(sp.re(S_source))) * 100
S_error_imag = (abs(sp.im(S_source) - sp.im(S_circuit)) / abs(sp.im(S_source))) * 100

print("S_error_real =",S_error_real, '%')
print("S_error_imag =",S_error_imag, '%\n')

# endregion


# region Vector-diagram

f2_real, f2_imag = f2.real, f2.imag
f3_real, f3_imag = f3.as_real_imag()
f4_real, f4_imag = f4.as_real_imag()
f5_real, f5_imag = f5.as_real_imag()
f6_real, f6_imag = f6.as_real_imag()
f7_real, f7_imag = f7.as_real_imag()
f8_real, f8_imag = f8.as_real_imag()
f9_real, f9_imag = f9.as_real_imag()
f10_real, f10_imag = f10.as_real_imag()
f11_real, f11_imag = f11.as_real_imag()

I1_real, I1_imag = I1.as_real_imag()
I2_real, I2_imag = I2.as_real_imag()
I3_real, I3_imag = I3.as_real_imag()
I4_real, I4_imag = I4.as_real_imag()
I5_real, I5_imag = I5.as_real_imag()
I6_real, I6_imag = I6_IK.real, I6_IK.imag

f_real = [f1, f2_real, f3_real, f4_real, f5_real, f6_real, f7_real, f8_real, f9_real, f10_real, f11_real, I1_real, I2_real, I3_real, I4_real, I5_real, I6_real]
f_imag = [f1, f2_imag, f3_imag, f4_imag, f5_imag, f6_imag, f7_imag, f8_imag, f9_imag, f10_imag, f11_imag, I1_imag, I2_imag, I3_imag, I4_imag, I5_imag, I6_imag]

# plot_complex_values_dots(f_real, f_imag)

# endregion


# region Re(S)

# 3.2 Determining the modes of operation of energy sources
print("sp.re(Se1) =", sp.re(Se1))
if sp.re(Se1) > 0:
    print("1. The source operates in generator mode")
else:
    print("1. The source is operating in consumer mode")

print("sp.re(Se2) =", sp.re(Se2))
if sp.re(Se2) > 0:
    print("2. The source operates in generator mode")
else:
    print("2. The source is operating in consumer mode")

print("sp.re(Sik) =", sp.re(Sik))
if sp.re(Sik) > 0:
    print("3. The source operates in generator mode")
else:
    print("3. The source is operating in consumer mode")

# endregion


# region Uc1 Uc2 Ul1
print("\nDetermine the readings of the voltmeters connected in parallel capacitors C1 and C2 as well as the "
      "inductance coil L1. ")
Uc1 = sp.re(-jXC1 * I2)
Uc2 = sp.re(-jXC2 * I5)
Ul1 = sp.re(jXL1 * I2)

print("Uc1 =", Uc1)
print("Uc2 =", Uc2)
print("Ul1 =", Ul1)

# endregion


# region Ia

Ia = sp.re(I1)

print("Ia =", Ia)

# endregion

import cmath

# Function to calculate power
def calculate_power(I, R, X):
    P = I.real**2 * R
    Q = I.real**2 * X
    return P, Q

# Function to calculate complex power
def calculate_complex_power(V, I):
    S = V * I.conjugate()
    return S

# Given values
I1 = complex(1.908, 0.917)
I2 = complex(4.09, 4.875)
I3 = complex(-0.011, 0.96)
I4 = complex(2.171, 4.918)
I5 = complex(-1.919, 0.043)
I6 = complex(-2.18, -3.958)
E1 = complex(21.766, -59.802)
E2 = complex(25, 25)
Xc1 = 31.847
Xc2 = 45.496
Xc3 = 15.924
Xl1 = 10.99
Xl2 = 21.98
Xl3 = 62.8
R1 = 11
R2 = 5
R3 = 10
R4 = 7

# Calculate powers
P1, Q1 = calculate_power(I1, R1, Xl1 - Xc1)
P2, Q2 = calculate_power(I2, R2, 0)
P3, Q3 = calculate_power(I3, R3, Xl3)
P4, Q4 = calculate_power(I4, R4, 0)
P5, Q5 = calculate_power(I5, 0, Xl2 - Xc2)
P6, Q6 = calculate_power(I6, 5, 0)

# Calculate power supplied by sources
SE1 = calculate_complex_power(E1, I1)
SE2 = calculate_complex_power(E2, I2)

# Calculate power consumed by the circuit
S12 = 0
S13 = calculate_complex_power(I3, I3.conjugate() * (Xl3 * 1j))
S14 = calculate_complex_power(I4, I4.conjugate() * (Xl2 * 1j))
S23 = calculate_complex_power(I2, I2.conjugate() * ((Xl1 - Xc1) * 1j))
S24 = calculate_complex_power(I6, I6.conjugate() * R2)
S34 = calculate_complex_power(I5, I5.conjugate() * ((Xl2 - Xc2) * 1j))

# Calculate total power supplied by sources
Stotal_sources = SE1 + SE2

# Calculate total power consumed by the circuit
Stotal_circuit = S12 + S13 + S14 + S23 + S24 + S34

# Print the results
print("Total power supplied by sources: S_sources =", Stotal_sources)
print("Total power consumed by the circuit: S_circuit =", Stotal_circuit)

# Check power balance
if abs(Stotal_sources - Stotal_circuit) < 1e-9:
    print("Баланс мощностей соблюдается.")
else:
    print("Баланс мощностей не соблюдается.")

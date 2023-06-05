import cmath

# Исходные данные
Ua = [63.38]  # Список значений напряжения Uа
Ub = [63.68]  # Список значений напряжения Ub
Uc = [63.2]  # Список значений напряжения Uc
Ia = [0.82]  # Список значений тока Ia
Ib = [0.81]  # Список значений тока Ib
Ic = [0.81]  # Список значений тока Ic

# Вычисление углов
phi_Ua = [cmath.phase(complex(Ua[i], 0)) for i in range(len(Ua))]
phi_Ub = [cmath.phase(complex(Ub[i], 0)) for i in range(len(Ub))]
phi_Uc = [cmath.phase(complex(Uc[i], 0)) for i in range(len(Uc))]
phi_Ia = [cmath.phase(complex(Ia[i], 0)) for i in range(len(Ia))]
phi_Ib = [cmath.phase(complex(Ib[i], 0)) for i in range(len(Ib))]
phi_Ic = [cmath.phase(complex(Ic[i], 0)) for i in range(len(Ic))]

# Вывод результатов
print("Углы для Ua:", phi_Ua)
print("Углы для Ub:", phi_Ub)
print("Углы для Uc:", phi_Uc)
print("Углы для Ia:", phi_Ia)
print("Углы для Ib:", phi_Ib)
print("Углы для Ic:", phi_Ic)
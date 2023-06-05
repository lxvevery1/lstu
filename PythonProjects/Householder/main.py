import numpy as np

def qr_eig(A, eps=1e-4, max_iter=100):
    n = A.shape[0]
    I = np.identity(n)
    V = I
    it = 0
    for i in range(max_iter):
        Q, R = np.linalg.qr(A)
        A = R @ Q
        V = V @ Q
        it = it+1
        if np.max(np.abs(A - np.diag(np.diag(A)))) < eps:
            break
    print("Q:", Q)
    print("R:", R)
    print("it:", it)
    print("A:", A)
    return np.diag(A), V

# array
A = np.array([ [4.935279658,	11.22995589,	7.490992356,	9.252651783,	3.132774354],
	[1.98774287, -4.155200862,	1.78913695, -0.601474896, -4.903054181 ],
	[					-14.85166852, -14.99269286, -17.98117655, -6.935448025,	3.670202377],
	[					3.110179479, 1.867629727, 1.115230495, -3.164764118, 3.172509008],
	[				-0.635350372, -2.132774354, -1.226824258, 1.39387817, -2.634138128]
	])
eigvals, eigvecs = qr_eig(A)
print("Eigenvalues:", eigvals)
print("Eigenvalues:", eigvecs)
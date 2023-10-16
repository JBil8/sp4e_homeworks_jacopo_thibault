import scipy.sparse.linalg as spla
import numpy as np
import matplotlib.pyplot as plt

def gmres(A, b, x0, tol, maxit, callback=None):
    """ GMRES algorithm for solving Ax = b """

    # Compute initial residual and its norm
    r0 = np.einsum('ij,j->i', A, x0) - b
    beta = np.linalg.norm(r0)

    # Initialize matrices and vectors
    V = np.zeros((len(b), maxit+1))
    V[:,0] = r0/beta
    g = np.zeros((maxit+1, 1))
    g[0] = beta
    Q = np.eye(maxit+1)
    H = np.zeros((maxit+1, maxit))

    i = 0
    while (abs(g[i]) > tol) and (i < maxit):
        
        # Arnoldi process to construct orthonormal basis
        w = np.dot(A, V[:, i])
        for j in range(i+1):
            H[j, i] = np.einsum('i,i->', w, V[:,j])
            w -= H[j, i] * V[:,j]
        H[i+1, i] = np.linalg.norm(w)
        V[:,i+1] = w / H[i+1, i]

        # Apply Givens rotations to Hessenberg matrix H
        H[:i+1, i] = np.einsum('ij,j->i', Q[:i+1, :i+1], H[:i+1, i])
        rho = H[i,i]
        H[i, i] = np.sqrt(rho**2 + H[i+1, i]**2)
        c = rho / H[i, i]
        s = H[i+1, i] / H[i, i]
        H[i+1, i] = 0

        # Update Q matrix for Givens rotations
        Q[i+1, :] = -s * Q[i, :]
        Q[i, :] = c * Q[i, :]
        Q[i, i+1] = s
        Q[i+1, i+1] = c

        # Apply Givens rotation to g vector
        g[i+1] = -s * g[i]
        g[i] = c * g[i]

        i += 1

        #if callback is not None:
            

    # Solve the least squares problem and compute the solution
    y = np.linalg.solve(H[:i, :i], g[:i])
    x = x0 + np.dot(V[:, :i], y)
    r = abs(g[i])

    return x, r, i




#############################################

if __name__ == "__main__":
    
    A = np.array([[8, 1], [1, 3]])
    b = np.array([2, 4])
    x0 = np.array([4, 4])
    x_intermediate = []

    optimized = gmres(A, b, x0, 1e-05, 100)
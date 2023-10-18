import numpy as np

def gmres(A, b, x0, maxit, tol=1e-5, callback=None):
    n = len(A)  # Get the dimension of the problem
    m = maxit  # Maximum number of iterations
    r = b - np.einsum('ij, j->i', A, x0)  # Calculate the initial residual
    b_norm = np.linalg.norm(b)  # Calculate the norm of the right-hand side vector
    error = np.linalg.norm(r) / b_norm  # Calculate the initial error

    sn = np.zeros(m)  # Sine components for Givens rotation
    cs = np.zeros(m)  # Cosine components for Givens rotation
    e1 = np.zeros(m + 1)  # unit vector
    e1[0] = 1
    e = [error]  # List to store error values
    r_norm = np.linalg.norm(r) 
    Q = np.zeros((n, m + 1))  # Matrix to store basis vectors
    Q[:, 0] = r / r_norm  # Set the  first column
    beta = r_norm * e1  
    H = np.zeros((m + 1, m))  # Hessenberg matrix

    for k in range(m):
        # Arnoldi process
        H, Q = arnoldi(A, Q, k + 1, H)

        # Apply Givens rotation to H
        H, cs, sn = apply_givens_rotation(H, cs, sn, k)

        # Update the residual vector
        beta[k + 1] = -sn[k] * beta[k]
        beta[k] = cs[k] * beta[k]
        error = abs(beta[k + 1]) / b_norm
        e.append(error)

        # Solve for y using the upper triangular Hessenberg matrix H
        y = np.linalg.lstsq(H[:m, :m], beta[:m], rcond=None)[0]

        # Update the solution
        x = x0 + np.einsum('ij, j->i', Q[:, :m], y)

        if callback:
            callback(x)  # Store the current solution in the callback function

        if error <= tol:  # Check if the error is below the tolerance
            break

    results = {'x': x, 'e': e}  # Store the final solution and error values in dictionary

    return results

def arnoldi(A, Q, k, H):
    q = np.einsum('ij, j->i', A, Q[:, k - 1])  # Create the next basis vector
    for i in range(k):
        H[i, k - 1] = np.einsum('i, i', Q[:, i], q)
        q -= H[i, k - 1] * Q[:, i]

    H[k, k - 1] = np.linalg.norm(q)  # Calculate the next entry in Hessenberg matrix
    Q[:, k] = q / H[k, k - 1]  # Update the basis vector

    return H, Q

def apply_givens_rotation(H, cs, sn, k):
    for i in range(k):
        temp = cs[i] * H[i, k] + sn[i] * H[i + 1, k]
        H[i + 1, k] = -sn[i] * H[i, k] + cs[i] * H[i + 1, k]
        H[i, k] = temp

    cs_k, sn_k = givens_rotation(H[k, k], H[k + 1, k])  # Compute the Givens rotation
    H[k, k] = cs_k * H[k, k] + sn_k * H[k + 1, k]
    H[k + 1, k] = 0.0
    cs[k] = cs_k  # Update cosine component
    sn[k] = sn_k  # Update sine component

    return H, cs, sn

def givens_rotation(v1, v2):
    if (v1==0):
        cs = 0
        sn = 1
    else:
        t = np.sqrt(v1**2 + v2**2)
        cs = v1 / t
        sn = v2 / t
    return cs, sn


# Example usage
if __name__ == '__main__':

    A = np.array([[8, 1], [1, 3]])
    b = np.array([2, 4])
    x0 = np.array([4, 4])
    max_iterations = 100
    threshold = 1e-5
    print("Exact solution:", np.linalg.solve(A, b))
    results = gmres(A, b, x0, max_iterations, threshold)
    print("Approximate solution:", results['x'])
    print("Residual:", results['e'])


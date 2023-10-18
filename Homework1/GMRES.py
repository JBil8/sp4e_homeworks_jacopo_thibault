import numpy as np

def gmres(A, b, x0, maxit, tol=1e-5, callback=None):
    n = len(A)
    m = maxit
    r = b - np.dot(A, x0)
    b_norm = np.linalg.norm(b)
    error = np.linalg.norm(r) / b_norm

    sn = np.zeros(m)
    cs = np.zeros(m)
    e1 = np.zeros(m + 1)
    e1[0] = 1
    e = [error]
    r_norm = np.linalg.norm(r)
    Q = np.zeros((n, m + 1))
    Q[:, 0] = r / r_norm
    beta = r_norm * e1
    H = np.zeros((m+1 , m))
    
    if callback:
        callback(x0) #store initial guess
    
    for k in range(m):
        
        H, Q = arnoldi(A, Q, k+1, H)
        H, cs, sn = apply_givens_rotation(H, cs, sn, k)
        beta[k + 1] = -sn[k] * beta[k]
        beta[k] = cs[k] * beta[k]
        error = abs(beta[k + 1]) / b_norm
        e.append(error)
        y = np.linalg.lstsq(H[:m, :m], beta[:m], rcond=None)[0]
        x = x0 + np.dot(Q[:, :m], y)
        if callback:
            callback(x)
        
        if error <= tol:
            break

    results = {'x': x, 'e': e}

    return results

def arnoldi(A, Q, k, H):
    q = np.dot(A, Q[:, k-1])
    #H = np.zeros((k+1 , k))
    for i in range(k):
        H[i, k-1] = np.dot(Q[:, i], q)
        q -= H[i, k-1] * Q[:, i]
    H[k, k-1] = np.linalg.norm(q)
    Q[:, k] = q / H[k, k-1]

    return H, Q

def apply_givens_rotation(H, cs, sn, k):
    for i in range(k):
        temp = cs[i] * H[i, k] + sn[i] * H[i + 1, k]
        H[i + 1, k] = -sn[i] * H[i, k] + cs[i] * H[i + 1, k]
        H[i, k] = temp

    cs_k, sn_k = givens_rotation(H[k, k], H[k + 1, k])
    H[k, k] = cs_k * H[k, k] + sn_k * H[k + 1, k]
    H[k + 1, k] = 0.0
    cs[k] = cs_k
    sn[k] = sn_k

    return H, cs, sn

def givens_rotation(v1, v2):
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


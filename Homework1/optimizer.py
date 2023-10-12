import scipy.optimize as opt
import numpy as np
import matplotlib.pyplot as plt

def optimizer(fun, x0): 
    # Check if fun is a function
    if not callable(fun):
        raise TypeError("fun must be a function")
    x_values = []
    
    results = opt.minimize(fun, x0, method="BFGS", callback=store_x)
    return results
    
    
def S(x):
    if x.shape != (2,):
        raise ValueError("x must be a 2D vector")
    A = np.array([[8, 1], [1, 3]])
    b = np.array([2, 4])
    return 0.5 * x.T @ A @ x - x.T @ b

"""
def S(x):
    A = np.array([[8, 1], [1, 3]])
    b = np.array([2, 4])
    return 0.5 * np.einsum('...i,ij,...j', x, A, x) - np.dot(x.T, b)
"""

def store_x(x):
    x_values.append(np.copy(x))


def plot_contour(fun, x_values):
    x = np.linspace(-5, 5, 100)
    y = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(x, y)
    Z = [fun(np.array([X[i, j], Y[i, j]])) for i in range(X.shape[0]) for j in range(X.shape[1])]
    Z = np.array(Z).reshape(X.shape)

    plt.figure()
    plt.contour(X, Y, Z, 20)
    plt.plot(x_values[:, 0], x_values[:, 1], 'r-')

    plt.show()
    

#############################################

if __name__ == "__main__":
    
    x_values = []
    optimized = optimizer(S, np.array([0, 0]))
    print(x_values)
    plot_contour(S, np.array(x_values))

    
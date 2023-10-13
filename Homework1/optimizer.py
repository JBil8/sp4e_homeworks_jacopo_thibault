import scipy.optimize as opt
import scipy.sparse.linalg as spla
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

"""
def optimizer(fun, x0): 
    # Check if fun is a function
    if not callable(fun):
        raise TypeError("fun must be a function")
    x_intermediate = []
    
    results = opt.minimize(fun, x0, method="BFGS", callback=store_x)
    return results
"""

def optimizer(A, b, x0, type="BFGS"):
    """ Optimizer for different methods """
    if A.shape != (2,2):
        raise ValueError("A must be a 2x2 matrix")
    if b.shape != (2,):
        raise ValueError("b must be a 2D vector")

    if type not in ["BFGS", "GMRES", "GMRES implementation"]:
        raise ValueError("type must be either BFGS, GMRES or GMRES implementation (BFGS is default)")
    
    #x_intermediate = []

    if type == "BFGS":
        results = opt.minimize(S, x0, method="BFGS", callback=store_x)
    elif type == "GMRES":
        results = spla.lgmres(A, b, x0, tol=1e-05, callback=store_x)
    elif type == "GMRES implementation":
        return "Not implemented yet"
    
def S(x):
    """ Function to optimize """
    if x.shape != (2,):
        raise ValueError("x must be a 2D vector")
    A = np.array([[8, 1], [1, 3]])
    b = np.array([2, 4])
    return 0.5 * x.T @ A @ x - x.T @ b


def store_x(x):
    """ Callback function to store the iteration points """
    x_intermediate.append(np.copy(x))


def plot_contour(fun, x_intermediate):
    """ Visualize the function and the iterations """
    # Create a meshgrid of points
    x = np.linspace(-5, 5, 100)
    y = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(x, y)

    # Evaluate the function at each point for the meshgrid and the iteration points
    Z = [fun(np.array([X[i, j], Y[i, j]])) for i in range(X.shape[0]) for j in range(X.shape[1])]
    Z = np.array(Z).reshape(X.shape)
    z_iterations = [fun(x_intermediate[i, :]) for i in range(len(x_intermediate))]

    # Plot the surface
    fig = plt.figure(figsize=(10,10))
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.2)

    # Plot contour lines on the surface
    contours = ax.contour3D(X, Y, Z, cmap='viridis')

    # Plot the iterations
    ax.plot(x_intermediate[:, 0], x_intermediate[:, 1], z_iterations, 'ro--')

    plt.show()
    

#############################################

if __name__ == "__main__":

    A = np.array([[8, 1], [1, 3]])
    b = np.array([2, 4])
    x0 = np.array([4, 4])
    x_intermediate = []

    optimized = optimizer(A, b, x0, type="GMRES")
    plot_contour(S, np.array(x_intermediate))

    
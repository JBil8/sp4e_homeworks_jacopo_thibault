import scipy.optimize as opt
import scipy.sparse.linalg as spla
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import argparse

import GMRES


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
        #return "GMRES implementation not working yet..."
        results = GMRES.gmres(A, b, x0, tol=1e-05, maxit=100, callback=store_x)
    return results



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
    x = np.linspace(-10, 10, 100)
    y = np.linspace(-10, 10, 100)
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

    parser = argparse.ArgumentParser(description="Optimization using various methods.")
    
    # A : list of 4 numbers (2x2 matrix)
    parser.add_argument("--A", type=float, nargs=4, required=True, metavar=('a11', 'a12', 'a21', 'a22'), help="2x2 matrix A in the form: a11 a12 a21 a22")
    # b : list of 2 numbers
    parser.add_argument("--b", type=float, nargs=2, required=True, metavar=('b1', 'b2'), help="2D vector b in the form: b1 b2")
    # Type of optimization
    parser.add_argument("--type", type=str, choices=["BFGS", "GMRES", "GMRES implementation"], default="BFGS", help="Type of optimization method. (default: BFGS))")
    # Make the plot optional
    parser.add_argument("--plot", action="store_true", help="Plot the results if this flag is set.")
    
    args = parser.parse_args()

    # Convert the list of numbers to numpy arrays
    A = np.array(args.A).reshape(2, 2)
    b = np.array(args.b)
    x0 = np.array([8, 8])
    x_intermediate = []

    optimized = optimizer(A, b, x0, type=args.type)
    print(optimized["x"])
    print(x_intermediate)
    
    if args.plot:
        plot_contour(S, np.array(x_intermediate))

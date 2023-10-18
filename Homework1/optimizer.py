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

    if type not in ["BFGS", "GMRES", "GMRES_implementation"]:
        raise ValueError("type must be either BFGS, GMRES or GMRES implementation (BFGS is default)")
    

    if type == "BFGS":
        results = opt.minimize(S, x0, method="BFGS", callback=store_x)
    elif type == "GMRES":
        results_array = spla.lgmres(A, b, x0, tol=1e-05, callback=store_x, atol=1e-05)
        results = {'x': results_array[0]}
    elif type == "GMRES_implementation":
        results = GMRES.gmres(A, b, x0, tol=1e-05, maxit=100, callback=store_x)
    return results


def S(x):
    """ Function to optimize """
    if x.shape != (2,):
        raise ValueError("x must be a 2D vector")
    #A = np.array([[8, 1], [1, 3]])
    #b = np.array([2, 4])
    return 0.5 * x.T @ A @ x - x.T @ b



def store_x(x):
    """ Callback function to store the iteration points """
    x_intermediate.append(np.copy(x))


def plot_contour(fun, x_intermediate):
    """ Visualize the function and the iterations """
    
    # Retrieve the result from the last iteration
    result = x_intermediate[-1]

    # Calculate the distance from the result to the initial point x0 to plot the right domain
    distances = [abs(point[0] - result[0]) for point in x_intermediate[:-1]], [abs(point[1] - result[1]) for point in x_intermediate[:-1]]
    max_distance = max(max(distances[0]), max(distances[1])) * 1.1 # Add 10% to the distance to make sure the result is in the plot
    
    # Create a meshgrid of points centered around the result
    x = np.linspace(result[0]-max_distance, result[0]+max_distance, 100) 
    y = np.linspace(result[1]-max_distance, result[1]+max_distance, 100)
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
    
    # Linear system matrix
    parser.add_argument("--matrix", nargs="+", type=float, action="append", help="A square matrix represented as a list.\n It is the linear system coefficient matrix")
    # Constant term
    parser.add_argument("--array", nargs="+", type=float, action="append", help="An array represented as a list.\n It is the constant term of the system")
    # Initial guess
    parser.add_argument("--x0", nargs="+", type=float, action="append", help="An array represented as a list.\n It is the initial gues for the solution")
    # Type of optimization
    parser.add_argument("--type", type=str, choices=["BFGS", "GMRES", "GMRES_implementation"], default="BFGS", help="Type of optimization method. (default: BFGS))")
    # Make the plot optional
    parser.add_argument("--plot", action="store_true", help="Plot the results if this flag is set.")
    
    args = parser.parse_args()

    b = np.asarray(args.array[0])
    n = b.shape[0]  #dimension of the system
    try:
        A = np.array(args.matrix).reshape(n,n)
    except ValueError as e:
        raise ValueError("Array and matrix dimensions not consistent")

    if args.x0:
        if(len(args.x0[0]) != n ):
            raise ValueError("The initial guess should be the same size as the constant term")
        else:
            x0 = np.asarray(args.x0[0])
    else:
        x0 = np.zeros(n)

    x_intermediate = []
    x_intermediate.append(np.copy(x0))

    optimized = optimizer(A, b, x0, type=args.type)
    if args.type == "GMRES":
        print("GMRES (scipy) solution:", optimized['x'])
    elif args.type == "GMRES_implementation":
        print("GMRES (from scratch) solution:", optimized['x'])
    elif args.type == "BFGS":
        print("BFGS solution:", optimized['x'])
    
    if args.plot:
        if n <=2:
            plot_contour(S, np.array(x_intermediate))
        else:
            print("Not possible to plot if the system dimension is greater than 2")

# Week 4 — Homework: Generalized Minimal Residual Method

## Table of Contents

- [Getting Started](#getting-started)
- [Dependencies](#dependencies)
- [Usage](#usage)

## Getting Started

Clone the repository : 
   ```bash
   git clone https://github.com/JBil8/sp4e_homeworks_jacopo_thibault.git
   cd sp4e_homeworks_jacopo_thibault/Homework1
   ```
## Dependencies

- **Python**: Version 3.x or higher
- **NumPy**: For numerical operations and matrix manipulations.
- **SciPy**: Provides functions for optimization and sparse linear algebra.
- **Matplotlib**: For plotting and visualizing the results.

To install the dependencies, you can use the following command:

```bash
pip install -r requirements.txt
```

## Usage

To run the code, follow the command structure below:
   ```bash
   python3 optimizer.py --A <matrix by rows> --b <list> [--x0 <list>] [--type {BFGS,GMRES,GMRES_implementation}] [--plot]
   ``` 
To reproduce the example in the exercise run:
   ```bash
   python3 optimizer.py --A 8. 1. 1. 3. --b 2. 4. --x0 4. 4. --type GMRES_implementation --plot
   ``` 


### Arguments
- `--A a11 a12 a21 a22`: Define the 2x2 matrix `A` with elements `a11`, `a12`, `a21` and `a22`.
- `--b b1 b2`: Define the 2D vector `b` with elements `b1` and `b2`.
- `--type`: *(Optional)* Specify the optimization method. Choices are `BFGS` from **scipy.optimize**, `GMRES` from **scipy.sparse.linalg** and `GMRES implementation`, the GMRES method implemented from scratch. Default is set to `BFGS`.
- `--plot`: *(Optional)* Include this flag if you want to visualize the function and the iterations.

For detailed help, run the following command:
   ```bash
   python3 optimizer.py -h
   ```

#### How it works

The function ```optimizer.py``` takes the matrix of the linear system ```A``` and the constant term ```b``` as separate inputs, as well as the algorithm to compute the solution.
For 2D problems it can also give a visual representation of the intermediate solutions with the function ```plot_contour```.
The module ```GMRES.py``` provides a simple implementation of the generalized minimal residual method from scratch with Arnoldi iterations and Givens rotations.
For more details see https://en.wikipedia.org/wiki/Generalized_minimal_residual_method


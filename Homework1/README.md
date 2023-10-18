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
   python3 optimizer.py --A a11 a12 a21 a22 --b b1 b2 [--type {BFGS,GMRES,GMRES_implementation}] [--plot]
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
# Week 6 — Homework: C++ classes

This program computes series based on the input type and dumps the results either to the console or to a file.

## Table of Contents

- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [How it works](#how-it-works)
- [Usage](#usage)
- [Questions](#questions)


## Getting started

To get a copy of the project up and running on your local machine for development and testing purposes, follow these steps:

1. Clone the repository

```bash
git clone https://github.com/JBil8/sp4e_homeworks_jacopo_thibault.git
cd sp4e_homeworks_jacopo_thibault/Homework2
```

2. Compile the program

```bash
mkdir build
cd build
cmake ..
make
```

## How it works

This code provides a rudimental object oriented implementation of the arithmetic series, the sum of inverse squares (which converges to $\pi^2/6$) and the Riemann integral. It also contains objects to dump the computed values either to screen, or to a file. Data from the file can be plotted with a python script.
The classes `ComputeArithmetic`, `ComputePi` and `RiemannIntegral` inherit from `Series`.
`PrintSeries` and `WriteSeries` inherit from `DumperSeries` and output the results on screen or in a file, respectively.
It is poissible to choose the number of terms used to compute the series, as well as the intervals used to compute the integral (`N`).

## Prerequisites

- A C++ compiler
- CMake for building the project

## Usage

Run the program using the following command structure:

```bash
./src/snippet <type> <N> <f> <dump> [<p>]
```

### Arguments

- `<type>`: Type of series to compute. Options are `pi`, `arithmetic`, or `riemann`. 
    - `pi` ($\pi =\sqrt{ 6\,  \Sigma_{k=1}^N {1 \over k^2}}$)
    - `arithmetic` ($S_n = \Sigma_{k=1}^N k$)
    - `riemann` ($\int_a^b f(x) dx = \lim_{N \to \infty} \Sigma_{k=1}^N f(x_k) \Delta x$)
- `<N>`: Number of iteration for pi and arithmetic / Number of discretizations for `riemann`
- `<f>`: Frequency of dumping
- `<dump>`: Dump type. Options are `print` to only print the results to the screen or `write` to write the results to a file and optionally visualize them.
- `[<p>]`: (Optional) Precision of the output.

Note that in some cases, e.g. for Riemann Integral, you will be prompted to enter additional parameters interactively.

#### Examples

1. Compute Pi series and print results to the console:
```bash
./src/snippet pi 1000 10 print
```

2. Compute Arithmetic series, write results to a file with a specified precision:
```bash
./src/snippet arithmetic 1000 10 write 5
```

3. Compute Riemann Integral, write results to a file:
```bash
./src/snippet riemann 1000 10 write
```


## Questions

#### Strategy to divide the work

The first step is to discuss the strategy together in a meeting. From this meeting, it appears that the Series and DumperSeries classes development is independent and that it is possible to work in parallel on this two tasks. One will develop The Series class while the other will develop the DumperSeries one. 

#### Objects memory allocation (Exrcise 2)

The use of `shared_ptr` takes care of the deletion of the pointers and automatically avoids memeory leaks. 

#### Series complexity (Exercise 5)

- The complexity would be of the order $N^2$ if for each dumper call the series is computed from scratch.
- By saving the `current_value` the complexity becomes order N as each time the dumper is called only an addition (and a square root operation in the `compue_pi` case) are performed
- Reducing the rounding errors over floating point operation by summing terms
reversely, does not affect the computational complexity of the algorithm.

#### Minimum number of interval for the integral (Exercise 6)

- *cubic* $N \approx 100$
- *cos* $N \approx 1000$
- *sin* $N \approx 200$

In general for our integration the error can be bounded by:
$|E| \leq max_{x \in [a,b]}$ |f'(x)| (b-a)h/2
Where $h$ is the size of the interval. 

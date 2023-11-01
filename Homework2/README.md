# Week 6 — Homework: C++ classes

This program computes series based on the input type and dumps the results either to the console or to a file.

## Table of Contents

- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
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

## Prerequisites

- A C++ compiler
- CMake for building the project

## Usage

Run the program using the following command structure:
```bash
./src/snippet <type> <N> <f> <dump> [<p>]
```

#### Arguments

- `<type>`: Type of series to compute. Options are `pi`, `arithmetic`, or `riemann`. 
    - `pi` (ADD FORMULA)
    - `arithmetic` (ADD FORMULA)
    - `riemann` (ADD FORMULA)
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

The first step is to discuss the strategy together in an in-person meeting. From this meeting, it appears that the Series and DumperSeries classes development is independant and that it is possible to work in parallel on this two tasks. One will develop The Series class while the other will develop the DumperSeries one. 
import argparse
import numpy as np
import matplotlib.pyplot as plt

def arg_parser():
    parser = argparse.ArgumentParser(description='Generate heat distribution')
    parser.add_argument('--num', type=int, default=1600,
                        help='number of particles (--num should be a squared number)')
    parser.add_argument('--xlim', action='store', type=float, default=[-1.,1.], nargs='+', 
                        help='Upper and lower limits for the x axis')
    parser.add_argument('--ylim', action='store', type=float, default=[-1.,1.], nargs='+',
                        help='Upper and lower limits for the y axis')
    parser.add_argument('--filename', type=str, default='input.csv',
                        help='Output filename')
    parser.add_argument('--plot', action='store_true', help="Plots the heat distribution")
    args = parser.parse_args()
    return args

def compute_temperature(x, y, xlim, ylim):
    return np.sin(2*np.pi*x)/(xlim[1]-xlim[0])

def compute_heat_source(x, y, xlim, ylim):
    return (2*np.pi/(xlim[1]-xlim[0]))**2*np.sin(2*np.pi*x)/(xlim[1]-xlim[0])

def plot_temperature(num, temperature, x_lim, y_lim):
    x_vals = np.linspace(x_lim[0], x_lim[1], int(np.sqrt(num)))
    y_vals = np.linspace(y_lim[0], y_lim[1], int(np.sqrt(num)))
    X, Y = np.meshgrid(x_vals, y_vals)
    Z = np.reshape(temperature, (int(np.sqrt(num)), int(np.sqrt(num))))

    plt.figure()
    plt.pcolormesh(X, Y, Z, shading='auto')
    plt.colorbar()  # shows the color scale
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Temperature Heatmap')
    plt.show()




if __name__ == '__main__':
    
    args = arg_parser()
    
    x_lim = args.xlim
    y_lim = args.ylim
    num = args.num
    filename = args.filename
    plot = args.plot

    # Check if num is a squared number
    if np.sqrt(num) != int(np.sqrt(num)):
        raise ValueError('num should be a squared number')

    x_vals = np.linspace(x_lim[0], x_lim[1], int(np.sqrt(num)))
    y_vals = np.linspace(y_lim[0], y_lim[1], int(np.sqrt(num)))

    positions = np.zeros((num, 3))
    velocity = np.zeros((num, 3))
    force = np.zeros((num, 3))
    masses = np.zeros((num, 1))
    temperature_rate = np.zeros((num, 1))
    temperature = np.zeros((num, 1))
    heat_source = np.zeros((num, 1))

    i = 0
    for x in x_vals:
        for y in y_vals:
            positions[i] = [x, y, 0]
            temperature[i] = compute_temperature(x, y, x_lim, y_lim)
            temperature_rate[i] = 0
            heat_source[i] = compute_heat_source(x, y, x_lim, y_lim)

            i += 1

    file_data = np.hstack((positions, velocity, force, masses, temperature, heat_source))
    np.savetxt(filename, file_data, delimiter=" ")

    if plot:
        plot_temperature(num, temperature, x_lim, y_lim)


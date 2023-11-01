import pandas as pd
import matplotlib.pyplot as plt
import sys

def get_separator(filename):
    extension = filename.split('.')[-1]
    separators = {
        'csv': ',',
        'txt': '\s+',
        'psv': '|'
    }
    return separators.get(extension, ',')

def read_data(filename):
    separator = get_separator(filename)
    data = pd.read_csv(filename, sep=separator)
    return data

def plot_data(data):
    plt.figure(figsize=(6, 6))
    
    plt.plot(data['Iterations'], data['Series_Value'], marker='o', linestyle='-', color='b', label='Series Value', markersize=2)
    plt.plot(data['Iterations'], data['Analytic_Prediction'], linestyle='--', color='r', label='Analytic Prediction')
    
    plt.title('Numerical Results')
    plt.xlabel('Iteration')
    plt.ylabel('Value')
    plt.grid(True)
    plt.legend()
    plt.show()

if __name__ == "__main__":
    filename = sys.argv[1]
    data = read_data(filename)
    plot_data(data)

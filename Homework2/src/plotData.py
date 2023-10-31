import pandas as pd
import matplotlib.pyplot as plt

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
    plt.figure(figsize=(10, 5))
    
    plt.plot(data['Iterations'], data['Series value'], marker='o', linestyle='-', color='b', label='Series Value')
    plt.plot(data['Iterations'], data['Analytic Prediction'], marker='s', linestyle='--', color='r', label='Analytic Prediction')
    
    plt.title('Numerical Results')
    plt.xlabel('Iteration')
    plt.ylabel('Value')
    plt.grid(True)
    plt.legend()
    plt.show()

if __name__ == "__main__":
    filename = input("Enter the filename: ")
    data = read_data(filename)
    plot_data(data)
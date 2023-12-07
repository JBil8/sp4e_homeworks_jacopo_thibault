import numpy as np

# Function to initialize the input matrix
def initialize_matrix(N):
    k = 2.0 * np.pi / N
    i, j = np.meshgrid(np.arange(N), np.arange(N), indexing='ij')
    return np.cos(k * i)


# Main program
N = 10
input_matrix = initialize_matrix(N)
output_matrix = np.fft.fft2(input_matrix)
print(np.round(output_matrix))


ki = np.fft.fftfreq(input_matrix.shape[0])
kj = np.fft.fftfreq(input_matrix.shape[1])

#store the 2d frequency grid in a 2d array
k2d = np.zeros((input_matrix.shape[0], input_matrix.shape[1], 2))
k2d[:,:,0] = ki[:,None]
k2d[:,:,1] = kj

print(k2d)
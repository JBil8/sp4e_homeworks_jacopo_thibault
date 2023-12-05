#ifndef FFT_HH
#define FFT_HH
/* ------------------------------------------------------ */
#include "matrix.hh"
#include "my_types.hh"
#include <fftw3.h>
/* ------------------------------------------------------ */

struct FFT {

  static Matrix<complex> transform(Matrix<complex>& m);
  static Matrix<complex> itransform(Matrix<complex>& m);

  static Matrix<std::complex<int>> computeFrequencies(int size);
};

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in) {
  UInt rows = m_in.rows();
  UInt cols = m_in.cols();

  // Allocate FFTW input and output arrays
  fftw_complex *in = reinterpret_cast<fftw_complex*>(m_in.data());
  fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * rows * cols);

  // Create and execute the plan
  fftw_plan plan = fftw_plan_dft_2d(rows, cols, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(plan);

  // Create result Matrix and copy FFTW output to it
  Matrix<complex> m_out(m_in.size());
  for (UInt i = 0; i < rows; ++i) {
    for (UInt j = 0; j < cols; ++j) {
      // Copying real and imaginary parts individually
      m_out(i, j) = complex(out[i * cols + j][0], out[i * cols + j][1]);
    }
  }
  //std::copy(out, out + rows * cols, reinterpret_cast<fftw_complex*>(m_out.data()));

  // Free memory
  fftw_destroy_plan(plan);
  fftw_free(out);

  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {
  return Matrix<complex>();
}

/* ------------------------------------------------------ */

inline Matrix<std::complex<int>> FFT::computeFrequencies(int size) {
  return Matrix<std::complex<int>>();
}

#endif  // FFT_HH

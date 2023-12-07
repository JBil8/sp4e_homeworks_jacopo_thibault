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
  
  int N = m_in.size();
  Matrix <complex> m_out(N);

  fftw_plan plan = fftw_plan_dft_2d(N, N,
                                    reinterpret_cast<fftw_complex*>(m_in.data()),
                                    reinterpret_cast<fftw_complex*>(m_out.data()),
                                    FFTW_FORWARD, FFTW_ESTIMATE);
  
  fftw_execute(plan);

  fftw_destroy_plan(plan);

  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {

  int N = m_in.size();
  Matrix<complex> m_out(N);

  fftw_plan plan = fftw_plan_dft_2d(N, N,
                                    reinterpret_cast<fftw_complex*>(m_in.data()),
                                    reinterpret_cast<fftw_complex*>(m_out.data()),
                                    FFTW_BACKWARD, FFTW_ESTIMATE);
  
  fftw_execute(plan);

  fftw_destroy_plan(plan);

  // Normalize the output
  m_out /= (N*N);

  return m_out;
  
}

/* ------------------------------------------------------ */

inline Matrix<std::complex<int>> FFT::computeFrequencies(int size) {

  Matrix<std::complex<int>> frequencies(size);

  for (auto&& entry : index(frequencies)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);

    if (i < size / 2)
      val.real(i);
    else
      val.real(i - size);

    if (j < size / 2)
      val.imag(j);
    else
      val.imag(j - size);

  }

  return frequencies;

}

#endif  // FFT_HH

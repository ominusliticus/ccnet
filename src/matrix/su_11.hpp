#pragma once

#include <complex>

#include "dense_matrix.hpp"

template<typename Precision>
class SU11Matrix : public Matrix<std::complex<Precision>> {
public:
    SU11Matrix();
    SU11Matrix(std::complex<Precision> entries[4]);
};

#pragma once

// SYCL Dependencies
#if USE_SYCL
  #define __NO_STD_MATH
  #define _SYCL_DISABLE_STL_HEADERS
  #include <sycl/sycl.hpp>
#endif

#include "matrix_concept.hpp"
#include "dense_matrix.hpp"

// Util
#include <util/error.hpp>
#include <util/try.hpp>

// STL
#include <utility>

namespace matrix {
enum class FactorType {
    RECURSIVE,
    NONRECURSIVE
};
}

using matrix::FactorType;

template<MatrixConcept MatrixType>
ErrorOr<std::pair<int, Matrix<typename MatrixType::Value>>> lu_factor(MatrixType const& mat,
                                                                      FactorType type);

template<MatrixConcept MatrixType>
ErrorOr<std::pair<std::vector<typename MatrixType::Value>,
                  Matrix<typename MatrixType::Value>>> qr_factor(MatrixType const& mat);

#include "impl/factor.tcc"

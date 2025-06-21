#pragma once

#include "matrix_concept.hpp"
#include "dense_matrix.hpp"

// Util
#include <util/error.hpp>
#include <util/try.hpp>

// STL
#include <optional>

template<MatrixConcept MatrixType>
ErrorOr<MatrixType> operator+(MatrixType const& mat_1, MatrixType const& mat_2);

template<MatrixConcept MatrixType>
ErrorOr<MatrixType> operator-(MatrixType const& mat_1, MatrixType const& mat_2);

template<MatrixConcept MatrixType>
MatrixType operator-(MatrixType const& mat_1);

template<MatrixConcept MatrixType>
ErrorOr<Matrix<typename MatrixType::Value>>
operator*(MatrixType const& mat_1, MatrixType const& mat_2);

template<MatrixConcept MatrixType>
MatrixType operator*(typename MatrixType::Value scalar, MatrixType const& mat);

#include "impl/arithmetic.tcc"

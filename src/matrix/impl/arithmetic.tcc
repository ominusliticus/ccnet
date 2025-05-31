#include <blas.hh>

template<MatrixConcept MatrixType>
auto
operator+(
    MatrixType const& mat_1, 
    MatrixType const& mat_2
) -> ErrorOr<MatrixType>
{
    // Early termination
    if (!(mat_1.get_dims() == mat_2.get_dims()))
        return ErrorType::INCOMPATIBLE_DIMENSIONS;

    using Index = typename MatrixType::Index;

    auto &[rows, cols] = mat_1.get_dims();
    MatrixType mat_3(mat_1);
    for (Index i{ 0 }; i < rows; ++i)
        for (Index j{ 0 }; j < cols; ++j)
            mat_3(i, j) = mat_1(i, j) + mat_2(i, j); 
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept MatrixType>
auto
operator-(
    MatrixType const& mat_1, 
    MatrixType const& mat_2
) -> ErrorOr<MatrixType>
{
    // Early termination
    if (!(mat_1.get_dims() == mat_2.get_dims()))
        return ErrorType::INCOMPATIBLE_DIMENSIONS;

    using Index = typename MatrixType::Index;

    auto &[rows, cols] = mat_1.get_dims();
    MatrixType mat_3(mat_1);
    for (Index i{ 0 }; i < rows; ++i)
        for (Index j{ 0 }; j < cols; ++j)
            mat_3(i, j) = mat_1(i, j) - mat_2(i, j); 
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept MatrixType>
auto
operator-(
    MatrixType const& mat_1
) -> MatrixType
{
    using Index = typename MatrixType::Index;
    using Value = typename MatrixType::Value;

    auto &[rows, cols] = mat_1.get_dims();
    MatrixType mat_2(mat_1);
    for (Index i{ 0 }; i < rows; ++i)
        for (Index j{ 0 }; j < cols; ++j)
            mat_2(i, j) = static_cast<Value>(-1.0) * mat_1(i, j); 
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept MatrixType>
auto
operator*(
    MatrixType const& mat_1,
    MatrixType const& mat_2
) -> ErrorOr<Matrix<typename MatrixType::Value>>
{
    // Early termination
    auto [rows, k_1] = mat_1.get_dims();
    auto [k_2, cols] = mat_2.get_dims();
    if (!(k_1 == k_2))
        return ErrorType::INCOMPATIBLE_DIMENSIONS;

    using Index = typename MatrixType::Index;
    using Value = typename MatrixType::Value;
    Index k{ k_1 };
    Matrix<Value> mat_3(rows, cols);
    blas::gemm(                                 // calculates alpha * A * B + beta * C
        blas::Layout::RowMajor,                 // blas::Layout -> memory layout
        blas::Op::NoTrans,                      // blas::Op     -> Transpose A before multiple
        blas::Op::NoTrans,                      // blas::Op     -> Transpose B before mulitple
        rows,                                   // number of rows in A
        cols,                                   // number of columns in B
        k,                                      // number of columns in A or rows in B
        static_cast<Value>(1.0),                // alpha
        mat_1.to_dense().data(),                // A
        std::max(static_cast<Index>(1), k),     // stride size of A
        mat_2.to_dense().data(),                // B
        std::max(static_cast<Index>(1), cols),  // stride size of B
        static_cast<Value>(0.0),                // beta
        mat_3.data(),                           // C
        std::max(static_cast<Index>(1), cols)   // stride size of C
    );
    return mat_3;
}


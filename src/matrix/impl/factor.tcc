// LAPACK 
#include <lapack.hh>

// STL
#include <vector>

template<MatrixConcept MatrixType>
auto
lu_factor(
    MatrixType const& mat,
    matrix::FactorType type
) -> ErrorOr<std::pair<int, Matrix<typename MatrixType::Value>>>
{
    using Value = typename MatrixType::Value;
    using Index = typename MatrixType::Index;

    Matrix<Value> factor{ std::move(mat.to_dense()) };
    auto [rows, cols] = factor.get_dims();
    std::vector<Value> pivot(std::min(static_cast<Index>(rows), static_cast<Index>(cols)));

    int64_t result_code{};
    switch (type)
    {
        case matrix::FactorType::RECURSIVE:
            result_code = lapack::getrf2(
                static_cast<Index>(rows),
                static_cast<Index>(cols),
                factor.data(),
                static_cast<Index>(cols),
                pivot.data()
            );
            break;
        case matrix::FactorType::NONRECURSIVE:
            result_code = lapack::getrf(
                static_cast<Index>(rows),
                static_cast<Index>(cols),
                factor.data(),
                static_cast<Index>(cols),
                pivot.data()
            );
            break;
    }

    if (result_code > 0) return ErrorType::SINGULAR_MATRIX;
    else if (result_code != 0) return ErrorType::FACTORIZATION_FAILED;
    int npivots = std::accumulate(pivot.begin(), pivot.end(), 0);
    int sign{ 1 ? npivots % 2 == 0 : -1 };
    return std::make_pair<int, Matrix<Value>>(sign, factor);
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept MatrixType>
static auto
construct_q_mat(
    MatrixType const& r_mat,
    std::vector<typename MatrixType::Value> const& reflections
) -> ErrorOr<Matrix<typename MatrixType::Value>>
{
    using Value = typename MatrixType::Value;
    using Index = typename MatrixType::Index;

    Index k{ reflections.size() };
    auto [rows, cols] = r_mat.get_dims();
    std::vector<Value> v(rows);
    Matrix<Value> q_mat = Matrix<Value>::Ident(rows);
    Matrix<Value> id = Matrix<Value>::Ident(rows);
    for (Index n{ k - 1 }; n >= 0; --n)
    {
        for (Index m{ 0 }; m < rows; ++m)
             v[m] = m < n ? static_cast<Value>(0.0) 
                          : (m == n ? static_cast<Value>(1.0) : TRY(r_mat(m, n)));

        q_mat = TRY(TRY((id - Matrix<Value>(v, v))) * q_mat);
    }
    return q_mat;
}

template<MatrixConcept MatrixType>
auto
qr_factor(
    MatrixType const& mat
) -> ErrorOr<std::pair<Matrix<typename MatrixType::Value>, Matrix<typename MatrixType::Value>>>
{
    using Value = typename MatrixType::Value;
    using Index = typename MatrixType::Index;

    Matrix<Value> r_mat{ std::move(mat.to_dense()) };
    auto [rows, cols] = r_mat.get_dims();
    std::vector<Value> reflections(std::min(static_cast<Index>(rows), static_cast<Index>(cols)));

    int64_t result_code{};
    result_code = lapack::geqrf(
        static_cast<Index>(rows),
        static_cast<Index>(cols),
        r_mat.data(),
        static_cast<Index>(cols),
        reflections.data()
    );

    if (result_code != 0) return ErrorType::FACTORIZATION_FAILED;
    
    Matrix<Value> q_mat = TRY(construct_q_mat(r_mat, reflections));
    return std::make_pair<Matrix<Value>, Matrix<Value>>(std::move(q_mat), std::move(r_mat));
}

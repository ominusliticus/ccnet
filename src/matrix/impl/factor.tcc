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

    std::int64_t result_code{};
    switch (type)
    {
        case matrix::FactorType::RECURSIVE:
            result_code = lapack::getrf2(
                static_cast<std::int64_t>(rows),
                static_cast<std::int64_t>(cols),
                factor.data(),
                static_cast<std::int64_t>(cols),
                pivot.data()
            );
            break;
        case matrix::FactorType::NONRECURSIVE:
            result_code = lapack::getrf(
                static_cast<std::int64_t>(rows),
                static_cast<std::int64_t>(cols),
                factor.data(),
                static_cast<std::int64_t>(cols),
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
    MatrixType const& a_mat,
    std::vector<typename MatrixType::Value> const& reflections
) -> ErrorOr<Matrix<typename MatrixType::Value>>
{
    using Value = typename MatrixType::Value;
    using Index = typename MatrixType::Index;

    auto [rows, cols] = a_mat.get_dims();
    Index k{ std::min(rows, cols) };
    std::vector<Value> v(rows);
    Matrix<Value> q_mat = Matrix<Value>::Ident(rows);
    Matrix<Value> id    = Matrix<Value>::Ident(rows);
    for (Index i{ 0 }; i < k; ++i)
    {
        Index m{ k - i - 1 };
        for (Index n{ 0 }; n < rows; ++n)
        {
            //          0       for n < m
            // v_m[n] = 1       for n == m
            //          A(i, k) for n > m
            v[n] = n < m ? static_cast<Value>(0.0) 
                         : (m == n ? static_cast<Value>(1.0) : TRY(a_mat(n, m)));
        }

        auto hess = Matrix<Value>(v, v);
        hess = TRY(id - reflections[m] * hess);
        q_mat = TRY(hess * q_mat);
    }
    return q_mat;
}

template<MatrixConcept MatrixType>
static auto
construct_r_mat(
    MatrixType const& a_mat
) -> Matrix<typename MatrixType::Value>
{
    using Value = typename MatrixType::Value;
    using Index = typename MatrixType::Index;

    auto [rows, cols] = a_mat.get_dims();
    Matrix<Value> r_mat(rows, cols);
    for (Index i = 0; i < cols; ++i)
        for (Index j = i; j < cols; ++j)
            r_mat[{i, j}] = a_mat[{i, j}];

    return r_mat;
}

template<MatrixConcept MatrixType>
auto
qr_factor(
    MatrixType const& mat
) -> ErrorOr<std::pair<Matrix<typename MatrixType::Value>, Matrix<typename MatrixType::Value>>>
{
    using Value = typename MatrixType::Value;
    using Index = typename MatrixType::Index;

    Matrix<Value> a_mat = mat.clone();
    auto [rows, cols]   = a_mat.get_dims();
    std::int64_t lda    = std::max(rows, static_cast<Index>(1));
    std::vector<Value> reflections(cols);

    std::int64_t result_code{};
    result_code = lapack::geqr2(
        static_cast<std::int64_t>(rows),
        static_cast<std::int64_t>(cols),
        a_mat.data(),
        lda,
        reflections.data()
    );

    if (result_code != 0) return ErrorType::FACTORIZATION_FAILED;
    
    Matrix<Value> q_mat = TRY(construct_q_mat(a_mat, reflections));
    Matrix<Value> r_mat = construct_r_mat(a_mat);
    return std::make_pair<Matrix<Value>, Matrix<Value>>(std::move(q_mat), std::move(r_mat));
}

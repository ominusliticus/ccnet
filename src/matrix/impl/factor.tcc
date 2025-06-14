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
auto
qr_factor(
    MatrixType const& mat
) -> ErrorOr<std::pair<std::vector<typename MatrixType::Value>,
                       Matrix<typename MatrixType::Value>>>
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
    
    // Matrix<Value> q_mat = construct_q_mat(reflections);
    return std::make_pair<std::vector<Value>, Matrix<Value>>(std::move(reflections), std::move(r_mat));
}

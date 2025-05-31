// STL
#include <cassert>
#include <complex>
#include <cstdint>
#include <utility>
#include <vector>

// CCNet
#include "matrix/block_matrix.hpp"
#include "matrix/dense_matrix.hpp"
#include "matrix/sparse_matrix.hpp"


// TODO: Need to really build a testing library that will sit untop of the CTest library
//       Largely, I want to build a project that has minimal third-party dependencies.

using Index     = std::size_t;
using IndexList = std::vector<std::pair<Index, Index>>;

template<typename Field>
auto
instantiate_matrix(
) -> void
{
    // dense matrices
    {
        Matrix<Field> m(10, 10);
        assert(m(3, 3) == static_cast<Field>(0.0));

        Matrix<Field> m2(std::move(m));
        assert(m2(4, 4) == static_cast<Field>(0.0));

        Matrix<Field> m3 = std::move(m2);
        assert((m3.get_dims() == std::make_pair<Index, Index>(10, 10)));
    }

    // sparse matrices
    {
        IndexList           index_list{{0, 0}, {1, 1}};
        std::vector<Field>  entries{ static_cast<Field>(1.0), static_cast<Field>(-1.0) };
        SparseMatrix<Field> sparse_m(std::move(index_list), std::move(entries));
        assert(sparse_m(0, 0).valu() == static_cast<Field>(1.0));

        SparseMatrix<Field> sparse_m2(std::move(sparse_m));
        assert(sparse_m2(1, 1).value() == static_cast<Field>(-1.0));

        SparseMatrix<Field>   sparse_m3 = std::move(sparse_m2);
        [[maybe_unused]] auto mat_dims  = std::make_pair<Index, Index>(2, 2);
        assert((sparse_m3.get_dims() == mat_dims));

        Matrix<Field> dense_m = sparse_m3.to_dense();
        assert((dense_m.get_dims() == mat_dims) && 
               (dense_m(0, 1).value() == sparse_m3(0, 1).value()));
    }

    // block matrices
    {
        IndexList           index_list{{0, 0}, {1, 1}, {2, 2}, {3, 3}};
        std::vector<Field>  entries{ 4, static_cast<Field>(1.0) };
        SparseMatrix<Field> sparse_m{ std::move(index_list), std::move(entries) };
        
        BlockDiagonalMatrix<SparseMatrix<Field>> block_m({sparse_m});
        assert(block_m(0, 0).value() == static_cast<Field>(1.0));

        BlockDiagonalMatrix<SparseMatrix<Field>> block_m2(std::move(block_m));
        assert(block_m(2, 3).value() == static_cast<Field>(0.0));

        BlockDiagonalMatrix<SparseMatrix<Field>> block_m3 = std::move(block_m2);
        assert((block_m3.get_dims() == std::make_pair<Index, Index>(4, 4)));

        Matrix<Field> dense_m = block_m.to_dense();
        assert(dense_m.data() != nullptr);
        assert(dense_m(3, 3).value() == static_cast<Field>(1.0));
    }
}

template<typename Field>
auto
instantiate_matrix(
    std::vector<Field>&& v,
    IndexList&&          index_list
) -> void
{
    // dense matrices
    {
        Matrix<Field> m(std::move(v));
        assert(m(0, 0) == static_cast<Field>(1.0));

        Matrix<Field> m2(std::move(m));
        assert(m2(1, 1) == static_cast<Field>(4.0));

        Matrix<Field> m3 = std::move(m2);
        assert((m3.get_dims() == std::make_pair<Index, Index>(2, 2)));
    }

    // sparse matrices
    {
        SparseMatrix<Field> sparse_m(std::move(index_list), std::move(v));
        assert(sparse_m(0, 0).valu() == static_cast<Field>(1.0));

        SparseMatrix<Field> sparse_m2(std::move(sparse_m));
        assert(sparse_m2(1, 1).value() == static_cast<Field>(-1.0));

        SparseMatrix<Field>   sparse_m3 = std::move(sparse_m2);
        [[maybe_unused]] auto mat_dims  = std::make_pair<Index, Index>(2, 2);
        assert((sparse_m3.get_dims() == mat_dims));

        Matrix<Field> dense_m = sparse_m3.to_dense();
        assert((dense_m.get_dims() == mat_dims) && 
               (dense_m(0, 1).value() == sparse_m3(0, 1).value()));

    }
}

auto
main(
) -> int
{
    // float test
    instantiate_matrix<float>();
    instantiate_matrix<float>(
        std::vector<float>{1.0f, 2.0f, 3.0f, 4.0f},
        IndexList{ {0, 0}, {0, 1}, {1, 0}, {1, 1} }
    );
    
    // double test
    instantiate_matrix<double>();
    instantiate_matrix<double>(
        std::vector<double>{1.0, 2.0, 3.0, 4.0},
        IndexList{ {0, 0}, {0, 1}, {1, 0}, {1, 1} }
    );

    // complex test
    using Field = std::complex<double>;
    instantiate_matrix<Field>();
    instantiate_matrix<Field>(
        std::vector<Field>{ {1.0, 0.0}, {2.0, 0.0}, {3.0, 0.0}, {4.0, 0.0} },
        IndexList{ {0, 0}, {0, 1}, {1, 0}, {1, 1} }
    );
    return 0;
}

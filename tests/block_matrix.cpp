// STL
#include <cassert>
#include <complex>
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

// CCNet
#include "matrix/block_matrix.hpp"
#include "matrix/dense_matrix.hpp"
#include "matrix/sparse_matrix.hpp"

using Index     = std::size_t;
using IndexList = std::vector<std::pair<Index, Index>>;
using Field     = std::complex<double>;


auto
main(
) -> int 
{
    Matrix<Field> mat_1 = Matrix<Field>::from_col_major(6, 3, {
         {8.53036, 0.02642}, {2.10276, 4.10980}, {1.09350, 7.52544},
         {5.21582, 5.89088}, {2.09163, 5.00381}, {8.53030, 1.84945},
         {1.40135, 8.49991}, {2.24332, 7.27830}, {6.48468, 8.67698},
         {1.39768, 0.58108}, {2.63978, 8.68788}, {2.76522, 8.89657},
         {0.91650, 3.48762}, {4.24442, 1.52522}, {7.92960, 8.37088},
         {6.28309, 0.74284}, {3.24625, 4.85203}, {7.75354, 7.79232}
    });
    SparseMatrix<Field> mat_2 {
        { {0, 0}, {1, 1}, {2, 2}, {3, 3} },
        { {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0}, {0.5, 0.5} }
    };
    BlockDiagonalMatrix<Matrix<Field>> block_mat {
        { mat_1, mat_2.to_dense() }
    };
    assert((block_mat.get_dims() == std::make_pair<Index, Index>(10, 7)));
    assert((block_mat(0, 0).value() == Field{8.53036, 0.02642}));
    assert((block_mat(2, 3).value() == Field{0.0, 0.0}));
    assert((block_mat(9, 6).value() == Field{0.5, 0.5}));
    
    return 0;
}

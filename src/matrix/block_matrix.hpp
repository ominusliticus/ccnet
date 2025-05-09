#pragma once

#include "dense_matrix.hpp"
#include "sparse_matrix.hpp"
#include "matrix_concept.hpp"


#include <cstdint>
#include <type_traits>
#include <utility>
#include <vector>


template<MatrixConcept Block>
class BlockDiagonalMatrix {
public:
    using Value     = typename Block::Value;
    using Index     = std::size_t;
    using Entries   = std::vector<Block>;
    using IndexList = std::vector<std::pair<Index, Index>>;

    // Constructors
    BlockDiagonalMatrix() = default;
    BlockDiagonalMatrix(Index n_entries);
    BlockDiagonalMatrix(Entries&& entries);

    // Copy and move operations
    BlockDiagonalMatrix(BlockDiagonalMatrix const& other);
    BlockDiagonalMatrix(BlockDiagonalMatrix&& other);

    BlockDiagonalMatrix& operator=(BlockDiagonalMatrix const& other);
    BlockDiagonalMatrix& operator=(BlockDiagonalMatrix&& other);

    // Access operations
    Value&       operator()(Index i, Index j);
    Value const& operator()(Index i, Index j) const;

    // Conversion to dense and sparse matrices
    Matrix<Value> to_dense();
    Matrix<Value> to_sparse();

    // Return matrix dimensions
    std::pair<Index, Index> get_dims();
private:
    Entries   m_entries;
};

#include "impl/block_matrix.tcc"

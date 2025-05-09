#pragma once

#include "dense_matrix.hpp"

#include <cstdint>
#include <type_traits>
#include <utility>
#include <vector>

template<typename Field>
class SparseMatrix {
public:
    using Value     = Field;
    using Index     = std::size_t;
    using Entries   = std::vector<Value>;
    using IndexList = std::vector<std::pair<Index, Index>>;

    // Constructors
    SparseMatrix() = default;
    SparseMatrix(Index n_entries);
    SparseMatrix(IndexList&& index_list, Entries&& entries);

    // Copy and move operations
    SparseMatrix(SparseMatrix const& other);
    SparseMatrix(SparseMatrix&& other);

    SparseMatrix& operator=(SparseMatrix const& other);
    SparseMatrix& operator=(SparseMatrix&& other);

    // Access operations
    Value&       operator()(Index i, Index j);
    Value const& operator()(Index i, Index j) const;

    // Conversion to dense matrices
    Matrix<Value> to_dense();

    // Return matrix dimension
    std::pair<Index, Index> get_dims();
private:
    IndexList m_index_list;
    Entries   m_entries;
};

#include "impl/sparse_matrix.tcc"

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
    SparseMatrix(SparseMatrix&& other) noexcept;

    SparseMatrix& operator=(SparseMatrix const& other);
    SparseMatrix& operator=(SparseMatrix&& other);

    // Access operations
    ErrorOr<Value&>       operator()(Index i, Index j);
    ErrorOr<Value const&> operator()(Index i, Index j) const;

    // Conversion to dense matrices
    Matrix<Value> to_dense();

    // Return matrix dimension
    std::pair<Index, Index> get_dims();
    std::pair<Index, Index> get_dims() const;

    // Iterators for easy matrix traversal
    struct Iterator {
        Iterator() noexcept = default;
        Iterator(
            std::pair<Index, Index>& indices_,
            Value* value_, 
            SparseMatrix<Field>* underlying_mat
        );

        // Iterator incrementor
        Iterator& operator++();
        Iterator& operator--();
        Iterator  operator++(int);
        Iterator  operator--(int);

        // For bounds checking
        bool operator==(Iterator const& itr);
        bool operator!=(Iterator const& itr);

        // Value accessing
        Iterator&       operator*() { return *this; }
        Iterator const& operator*() const { return *this; }

        std::pair<Index, Index>& indices;
        Value*                   value;

    private:
        SparseMatrix<Field>* underlying_matrix;
    };

    // Iterators to abstract data traversal
    Iterator        begin();
    Iterator const& cbegin();
    Iterator        end();
    Iterator const& cend();
private:
    IndexList m_index_list;
    Entries   m_entries;
};

#include "impl/sparse_matrix.tcc"

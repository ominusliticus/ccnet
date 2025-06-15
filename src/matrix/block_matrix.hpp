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
    using Value    = typename Block::Value;
    using Index    = std::size_t;
    using Entries  = std::vector<Block>;
    using DimsList = std::vector<std::pair<Index, Index>>;

    // Constructors
    BlockDiagonalMatrix() = default;
    BlockDiagonalMatrix(Entries&& entries);

    // Copy and move operations
    BlockDiagonalMatrix(BlockDiagonalMatrix const& other);
    BlockDiagonalMatrix(BlockDiagonalMatrix&& other) noexcept;

    BlockDiagonalMatrix& operator=(BlockDiagonalMatrix const& other);
    BlockDiagonalMatrix& operator=(BlockDiagonalMatrix&& other);

    // Access operations
    ErrorOr<Value&>       operator()(Index i, Index j);
    ErrorOr<Value const&> operator()(Index i, Index j) const;
    bool                  operator==(BlockDiagonalMatrix const& other);

    // Falliable comparison
    ErrorOr<bool> eq(BlockDiagonalMatrix const& other);

    // Conversion to dense matrices
    Matrix<Value> to_dense();

    // Return matrix dimensions
    std::pair<Index, Index> get_dims();
    std::pair<Index, Index> get_dims() const;

    // Iterators for easy matrix traversal
    struct Iterator {
        Iterator() noexcept = default;
        Iterator(
            typename Block::Iterator const&   current_block_itr_,
            Index                       current_block_index_,
            BlockDiagonalMatrix<Block>* underlying_mat
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

        typename Block::Iterator& current_block_itr;
        Index                     current_block_index;

    private:
        BlockDiagonalMatrix<Block>* underlying_matrix; 
    };

    // Iterators to abstract data traversal
    Iterator        begin();
    Iterator const& cbegin();
    Iterator        end();
    Iterator const& cend();
private:
    DimsList m_dims_list;
    Entries  m_entries;
};

#include "impl/block_matrix.tcc"
#include "impl/block_matrix_iterator.tcc"

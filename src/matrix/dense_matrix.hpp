#pragma once

// Util
#include <util/error.hpp>
#include <util/try.hpp>

// STL
#include <cstdint>
#include <memory>
#include <vector>
#include <utility>

template<typename Field>
class Matrix
{
public:
    using Value   = Field;
    using Index   = std::size_t;
    using Entries = std::vector<Value>;

    // Constructors
    Matrix() noexcept = default;
    Matrix(Index rows, Index cols);
    Matrix(Entries&& entries);

    // Copy and move operations
    Matrix(Matrix const& other);
    Matrix(Matrix&& other) noexcept;
    
    Matrix& operator=(Matrix const& other);
    Matrix& operator=(Matrix&& other);

    // Access operations
    ErrorOr<Value&>       operator()(Index i, Index j);
    ErrorOr<Value const&> operator()(Index i, Index j) const;

    // Conversion to dense: for compatibility
    Matrix<Value>&       to_dense() { return *this; }
    Matrix<Value> const& to_dense() const {return *this; }
    
    // Return matrix dims
    std::pair<Index, Index> get_dims();
    std::pair<Index, Index> get_dims() const;

    // Get access to underlying data
    Value*       data()       { return m_entries.data(); };
    Value const* data() const { return m_entries.data(); };

    // Iterators for easy matrix traversal
    struct Iterator {
        Iterator() noexcept = default;
        Iterator(std::pair<Index, Index> indices_, Value* value_, Matrix<Value>* mat);

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

        std::pair<Index, Index> indices;
        Value*                  value;
        
    private:
        Matrix<Value>* underlying_matrix;
    };

    // Iterators to abstract data traversal
    Iterator        begin();
    Iterator const& cbegin();
    Iterator        end();
    Iterator const& cend();

private:
    Entries m_entries;
    Index   m_rows;
    Index   m_cols;

};

#include "impl/dense_matrix.tcc"
#include "impl/dense_matrix_iterator.tcc"

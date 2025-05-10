#pragma once

#include <cstdint>
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
    Matrix() = default;
    Matrix(Index rows, Index cols);
    Matrix(Entries&& entries);

    // Copy and move operations
    Matrix(Matrix const& other);
    Matrix(Matrix&& other) noexcept;
    
    Matrix& operator=(Matrix const& other);
    Matrix& operator=(Matrix&& other);

    // Access operations
    Value&       operator()(Index i, Index j);
    Value const& operator()(Index i, Index j) const;
    
    // Return matrix dims
    std::pair<Index, Index> get_dims();
    std::pair<Index, Index> get_dims() const;

    // Is matrix dense?
    static bool is_dense() { return true; }
private:
    std::vector<Field> m_entries;
    Index      m_rows;
    Index      m_cols;
};

#include "impl/dense_matrix.tcc"

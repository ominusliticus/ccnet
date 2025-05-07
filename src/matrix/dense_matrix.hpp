#pragma once

#include <vector>
#include <cstdint>

template<typename Field>
class Matrix
{
public:
    using Value   = Field;
    using Index   = std::uint16_t;
    using Entries = std::vector<Field>;


    Matrix() = default;
    Matrix(Index rows, Index cols);
    Matrix(std::vector<Value> entris);

    Value&       operator()(Index i, Index j);
    Value const& operator()(Index i, Index j) const;
private:
    std::vector<Field> m_entries;
    Index      m_rows;
    Index      m_cols;
};

#include "impl/dense_matrix.tcc"

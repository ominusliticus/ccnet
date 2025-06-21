#include <utility>
#include <cmath>

#include <print.hpp>

template<typename Field>
Matrix<Field>::Iterator::Iterator(
    std::pair<Index, Index> indices_,
    Value*                  value_,
    Matrix<Value>*          mat
)
  : indices{ indices_ }
  , value{ value_ }
  , underlying_matrix{ mat }
{}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::Iterator::operator++(
) -> Matrix<Field>::Iterator&
{
    auto [i, j] = indices;
    if (j >= underlying_matrix->m_cols) 
    {
        j = 0;
        ++i;
    }
    Index i_ = i < underlying_matrix->m_rows ? i : underlying_matrix->m_rows - 1;
    Index j_ = j < underlying_matrix->m_cols ? j : underlying_matrix->m_cols - 1;
    indices = std::make_pair(i, j);
    value = &underlying_matrix->m_entries[i_ + j_ * underlying_matrix->m_rows];
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::Iterator::operator--(
) -> Matrix<Field>::Iterator& 
{
    auto [i, j] = indices;
    if (j <= 0) 
    {
        j = underlying_matrix->m_cols - 1;
        --i;
    }
    Index i_ = i > 0 ? i : 0;
    Index j_ = j > 0 ? j : 0;
    indices = std::make_pair(i, j);
    value = &underlying_matrix->m_entries[i_ + j_ * underlying_matrix->m_rows];
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::Iterator::operator++(
    int
) -> Matrix<Field>::Iterator
{
    auto old = *this;
    auto [i, j] = indices;
    if (j >= underlying_matrix->m_cols) 
    {
        j = 0;
        ++i;
    }
    Index i_ = i < underlying_matrix->m_rows ? i : underlying_matrix->m_rows - 1;
    Index j_ = j < underlying_matrix->m_cols ? j : underlying_matrix->m_cols - 1;
    indices = std::make_pair(i, j);
    value = &underlying_matrix->m_entries[i_ + j_ * underlying_matrix->m_rows];
    return old;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::Iterator::operator--(
    int
) -> Matrix<Field>::Iterator 
{
    auto old = *this;
    auto [i, j] = indices;
    if (j <= 0) 
    {
        j = underlying_matrix->m_cols - 1;
        --i;
    }
    Index i_ = i > 0 ? i : 0;
    Index j_ = j > 0 ? j : 0;
    indices = std::make_pair(i, j);
    value = &underlying_matrix->m_entries[i_ + j_ * underlying_matrix->m_rows];
    return old;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::Iterator::operator==(
    Iterator const& other
) -> bool
{
    auto [i, j] = indices;
    auto [oi, oj] = other.indices;
    return (i == oi) && (j == oj) && (value == other.value);
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::Iterator::operator!=(
    Iterator const& other
) -> bool
{
    return !(this->operator==(other));
}

#include <utility>
#include <cmath>

#include <print.hpp>

template<typename Field>
SparseMatrix<Field>::Iterator::Iterator(
    std::pair<Index, Index>& indices_,
    Value*                   value_,
    SparseMatrix<Field>*     underlying_mat
)
  : indices{ indices_ }
  , value{ value_ }
  , underlying_matrix{ underlying_mat }
{}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::Iterator::operator++(
) -> SparseMatrix<Field>::Iterator&
{
    indices = *(&indices + 1);
    ++value;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::Iterator::operator--(
) -> SparseMatrix<Field>::Iterator& 
{
    indices = *(&indices - 1);
    --value;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::Iterator::operator++(
    int
) -> SparseMatrix<Field>::Iterator
{
    auto old = *this;
    indices = *(&indices + 1);
    ++value;
    return old;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::Iterator::operator--(
    int
) -> SparseMatrix<Field>::Iterator 
{
    auto old = *this;
    indices = *(&indices - 1);
    --value;
    return old;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::Iterator::operator==(
    Iterator const& other
) -> bool
{
    auto [i, j] = indices;
    auto [oi, j] = other.indices;
    return (i == oi) && (j == oj) && (value == other.value);
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::Iterator::operator!=(
    Iterator const& other
) -> bool
{
    return !(this->operator==(other));
}

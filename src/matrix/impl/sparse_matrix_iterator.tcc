#include <utility>
#include <cmath>

#include <print.hpp>

template<typename Field>
SparseMatrix<Field>::Iterator::Iterator(
    IndexList::iterator        indices_,
    typename Entries::iterator value_,
    SparseMatrix<Field>*       underlying_mat
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
    ++indices;
    ++value;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::Iterator::operator--(
) -> SparseMatrix<Field>::Iterator& 
{
    --indices;
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
    ++indices;
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
    --indices;
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
    auto [i, j] = *indices;
    auto [oi, oj] = *other.indices;
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

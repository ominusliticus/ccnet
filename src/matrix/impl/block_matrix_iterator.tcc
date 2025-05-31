#include <utility>
#include <cmath>

#include <print.hpp>

template<MatrixConcept Block>
BlockDiagonalMatrix<Block>::Iterator::Iterator(
    typename Block::Iterator const& current_block_itr_,
    Index                           current_block_index_,
    BlockDiagonalMatrix<Block>*     underlying_mat

)
  : current_block_itr{ current_block_itr_ }
  , current_block_index{ current_block_index_ }
  , underlying_matrix{ underlying_mat }
{}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::Iterator::operator++(
) -> BlockDiagonalMatrix<Block>::Iterator&
{
    if (current_block_itr == underlying_matrix->m_entries[current_block_index].end())
        current_block_itr = underlying_matrix->m_entries[++current_block_index].begin();
    else
        ++current_block_itr;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::Iterator::operator--(
) -> BlockDiagonalMatrix<Block>::Iterator& 
{
    if (current_block_itr == underlying_matrix->m_entries[current_block_index].begin())
        current_block_itr = underlying_matrix->m_entries[--current_block_index].end();
    else
        --current_block_itr;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::Iterator::operator++(
    int
) -> BlockDiagonalMatrix<Block>::Iterator
{
    if (current_block_itr == underlying_matrix->m_entries[current_block_index].end())
        current_block_itr = underlying_matrix->m_entries[++current_block_index].begin();
    else
        ++current_block_itr;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::Iterator::operator--(
    int
) -> BlockDiagonalMatrix<Block>::Iterator 
{
    if (current_block_itr == underlying_matrix->m_entries[current_block_index].begin())
        current_block_itr = underlying_matrix->m_entries[--current_block_index].end();
    else
        --current_block_itr;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::Iterator::operator==(
    Iterator const& other
) -> bool
{
    bool same_block_itr   = current_block_itr == other.current_block_itr;
    bool same_block_index = current_block_index == other.current_block_index;
    bool same_mat         = underlying_matrix == other.underlying_matrix;
    return same_block_itr && same_block_index && same_mat;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::Iterator::operator!=(
    Iterator const& other
) -> bool
{
    return !(this->operator==(other));
}


#include <cmath>
#include <utility>


template<typename Field>
BlockDiagonalMatrix<Field>::BlockDiagonalMatrix(
    Index n_entries
) : m_entries{ std::move(Entries(n_entries)) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
BlockDiagonalMatrix<Field>::BlockDiagonalMatrix(
    IndexList&& index_list,
    Entries&&   entries
) : m_entries{ std::move(entries) }
{
    Index n{ static_cast<Index>(std::sqrt(entries.size())) };
    m_rows = n;
    m_cols = n;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
BlockDiagonalMatrix<Field>::BlockDiagonalMatrix(
    BlockDiagonalMatrix<Field> const& other
) : m_entries{ other.m_entries }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
BlockDiagonalMatrix<Field>::BlockDiagonalMatrix(
    BlockDiagonalMatrix<Field>&& other
) noexcept
  : m_entries{ std::move(other.m_entries) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
BlockDiagonalMatrix<Field>::operator=(
    BlockDiagonalMatrix<Field> const& other

) -> BlockDiagonalMatrix<Field>&
{
    m_entries = other.entries;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto 
BlockDiagonalMatrix<Field>::operator=(
    BlockDiagonalMatrix<Field>&& other
) -> BlockDiagonalMatrix<Field>&
{
    m_entries = std::move(other.entries);
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
BlockDiagonalMatrix<Field>::operator()(
    Index i,
    Index j
) -> Value&
{
    return m_entries[i * m_cols + j];
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
BlockDiagonalMatrix<Field>::operator()(
    Index i,
    Index j
) const -> Value const&
{
    return m_entries[i * m_cols + j];
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
BlockDiagonalMatrix<Field>::to_dense(
) -> Matrtix<Field>
{
    Index rows{ 0 };
    Index cols{ 0 };
    for (auto const& indices : m_index_list)
    {
        rows = indices.get<0>() ? rows < max_dims.get<0>() : rows;
        cols = indices.get<0>() ? cols < max_dims.get<0>() : cols;
    }
    Matrix<Field> mat(rows, cols);
    Index pos{ 0 };
    for (auto const& [i, j] : m_index_list)
         mat(i, j) = m_entries[pos++];

    return mat;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
BlockDiagonalMatrix<Field>::to_dense(
) -> Matrtix<Field>
{
    Index rows{ 0 };
    Index cols{ 0 };
    for (auto const& indices : m_index_list)
    {
        rows = indices.get<0>() ? rows < max_dims.get<0>() : rows;
        cols = indices.get<0>() ? cols < max_dims.get<0>() : cols;
    }
    Matrix<Field> mat(rows, cols);
    Index pos{ 0 };
    for (auto const& [i, j] : m_index_list)
         mat(i, j) = m_entries[pos++];

    return mat;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
get_dims(
) -> std::pair<Index, Index>
{
    auto add_pairs = [](
        std::pair<Index, Index> a, std::pari<Index, Index> b
    ) -> std::pair<Index, Index> {
        return std::make_pair(a.get<0>() + b.get<0>(), a.get<1>() + b.get<1>());
    };
    auto dim = std::make_pair<Index, Index>>(0, 0);
    for (auto const& mat : m_entries)
        dim = add_pair(dim, mat.get_dims())
    return dim;
}

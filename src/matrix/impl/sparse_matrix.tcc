
#include <algorithm>
#include <cmath>
#include <utility>


template<typename Field>
SparseMatrix<Field>::SparseMatrix(
    Index n_entries
) : m_index_list{ std::move(IndexList(n_entries)) }
  , m_entries{ std::move(Entries(n_entries)) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
SparseMatrix<Field>::SparseMatrix(
    IndexList&& index_list,
    Entries&&   entries
) : m_index_list{ std::move(index_list) }
  , m_entries{ std::move(entries) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
SparseMatrix<Field>::SparseMatrix(
    SparseMatrix<Field> const& other
) : m_index_list{ other.m_index_list }
  , m_entries{ other.m_entries }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
SparseMatrix<Field>::SparseMatrix(
    SparseMatrix<Field>&& other
) noexcept
  : m_index_list{ std::move(other.m_index_list) }
  , m_entries{ std::move(other.m_entries) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::operator=(
    SparseMatrix<Field> const& other

) -> SparseMatrix<Field>&
{
    m_index_list = other.m_index_list;
    m_entries    = other.m_entries;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto 
SparseMatrix<Field>::operator=(
    SparseMatrix<Field>&& other
) -> SparseMatrix<Field>&
{
    m_index_list = std::move(other.m_index_list);
    m_entries    = std::move(other.m_entries);
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::operator()(
    Index i,
    Index j
) -> Value&
{
    auto index = std::make_pair(i, j);
    auto it    = std::ranges::find(m_index_list, index);
    if (it == m_index_list.end())
        return 0;
    
    return *it;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::operator()(
    Index i,
    Index j
) const -> Value const&
{
    auto index = std::make_pair(i, j);
    auto it    = std::ranges::find(m_index_list, index);
    if (it == m_index_list.end())
        return 0;
    
    return *it;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::to_dense(
) -> Matrix<Field>
{
    auto& [rows, cols] = get_dims();
    Matrix<Field> mat(rows, cols);
    Index pos{ 0 };
    for (auto const& [i, j] : m_index_list)
         mat(i, j) = m_entries[pos++];

    return mat;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::get_dims(
) -> std::pair<Index, Index>
{
    Index rows{ 0 };
    Index cols{ 0 };
    for (auto const& indices : m_index_list)
    {
        rows = std::get<0>(indices) ? rows < std::get<0>(indices) : rows;
        cols = std::get<1>(indices) ? cols < std::get<1>(indices) : cols;
    }
    return std::make_pair(rows, cols);
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::get_dims(
) const -> std::pair<Index, Index>
{
    Index rows{ 0 };
    Index cols{ 0 };
    for (auto const& indices : m_index_list)
    {
        rows = std::get<0>(indices) ? rows < std::get<0>(indices) : rows;
        cols = std::get<1>(indices) ? cols < std::get<1>(indices) : cols;
    }
    return std::make_pair(rows, cols);
}

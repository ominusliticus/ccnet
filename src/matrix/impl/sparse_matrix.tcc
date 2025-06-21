
#include <algorithm>
#include <cmath>
#include <utility>


template<typename Field>
SparseMatrix<Field>::SparseMatrix(
    Index n_entries
) : m_index_list(n_entries)
  , m_entries(n_entries)
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
) -> ErrorOr<Value&>
{
    auto [rows, cols] = get_dims();
    auto index        = std::make_pair(i, j);
    auto it           = std::ranges::find(m_index_list, index);
    if (it == m_index_list.end())
        return (i < rows) && (j < cols) ? ErrorType::INDEX_NOT_IN_LIST : ErrorType::OUT_OF_BOUNDS;
    
    return m_entries[static_cast<std::ptrdiff_t>(it - m_index_list.begin())];
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::operator()(
    Index i,
    Index j
) const -> ErrorOr<Value const&>
{
    auto [rows, cols] = get_dims();
    auto index        = std::make_pair(i, j);
    auto it           = std::ranges::find(m_index_list, index);
    if (it == m_index_list.end())
        return (i < rows) && (j < cols) ? ErrorType::INDEX_NOT_IN_LIST : ErrorType::OUT_OF_BOUNDS;
    
    return m_entries[static_cast<std::ptrdiff_t>(it - m_index_list.begin())];
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::operator[](
    std::pair<Index, Index>&& indices
) -> Value&
{
    auto it = std::ranges::find(m_index_list, indices);
    return m_entries[static_cast<std::ptrdiff_t>(it - m_index_list.begin())];
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::operator[](
    std::pair<Index, Index>&& indices
) const -> Value const&
{
    auto it = std::ranges::find(m_index_list, indices);
    return m_entries[static_cast<std::ptrdiff_t>(it - m_index_list.begin())];
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::eq(
    SparseMatrix<Field> const& other,
    double tol
) -> ErrorOr<bool>
{
    auto const [orows, ocols] = other.get_dims();
    auto const [mrows, mcols] = get_dims();
    if (!((orows == mrows) && (ocols == mcols))) return ErrorType::INCOMPATIBLE_DIMENSIONS;

    bool is_same = true;
    auto is_close = [tol](auto left, auto right) -> bool 
    { 
        return std::abs(left - right) < tol; 
    };
    for (Index n{ 0 }; n < m_entries.size(); ++n)
        is_same &= is_close(m_entries[n], other.m_entries[n]);
    return is_same;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::to_dense(
) -> Matrix<Field>
{
    auto [rows, cols] = get_dims();
    Matrix<Field> mat(rows, cols);
    Index pos{ 0 };
    for (auto const& [i, j] : m_index_list)
    {
        mat[{i, j}] = m_entries[pos++];
    }

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
        rows = rows < std::get<0>(indices) ? std::get<0>(indices) : rows;
        cols = cols < std::get<1>(indices) ? std::get<1>(indices) : cols;
    }
    return std::make_pair(rows + 1, cols + 1);
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
        rows = rows < std::get<0>(indices) ? std::get<0>(indices) : rows;
        cols = cols < std::get<1>(indices) ? std::get<1>(indices) : cols;
    }
    return std::make_pair(rows + 1, cols + 1);
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::begin(
) -> SparseMatrix<Field>::Iterator
{
    return { m_index_list.begin(), m_entries.begin(), this };
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::cbegin(
) -> SparseMatrix<Field>::Iterator const&
{
    return { m_index_list.begin(), m_entries.begin(), this };
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::end(
) -> SparseMatrix<Field>::Iterator
{
    return { m_index_list.end(), m_entries.end(), this };
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
SparseMatrix<Field>::cend(
) -> SparseMatrix<Field>::Iterator const&
{
    return { m_index_list.end(), m_entries.end(), this };
}

#include <utility>
#include <cmath>

#include <print.hpp>

template<typename Field>
Matrix<Field>::Matrix(
    Index rows,
    Index cols
) : m_entries{ std::move(Entries(rows * cols, static_cast<Field>(0))) }
  , m_rows{ rows }
  , m_cols{ cols }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
Matrix<Field>::Matrix(
    Entries&& entries
) : m_entries{ std::move(entries) }
{
    Index n{ static_cast<Index>(std::sqrt(m_entries.size())) };
    println("Vector length", m_entries.size());
    println("Square matrix dim", n);
    m_rows = n;
    m_cols = n;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
Matrix<Field>::Matrix(
    Matrix<Field> const& other
) : m_entries{ other.m_entries }
  , m_rows{ other.m_rows }
  , m_cols{ other.m_cols }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
Matrix<Field>::Matrix(
    Matrix<Field>&& other
) noexcept
  : m_entries{ std::move(other.m_entries) }
  , m_rows{ std::move(other.m_rows) }
  , m_cols{ std::move(other.m_cols) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::operator=(
    Matrix<Field> const& other

) -> Matrix<Field>&
{
    m_entries = other.m_entries;
    m_rows    = other.m_rows;
    m_cols    = other.m_cols;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto 
Matrix<Field>::operator=(
    Matrix<Field>&& other
) -> Matrix<Field>&
{
    m_entries = std::move(other.m_entries);
    m_rows    = std::move(other.m_rows);
    m_cols    = std::move(other.m_cols);
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::operator()(
    Index i,
    Index j
) -> ErrorOr<Value&>
{
    if ((i < m_rows) && (j < m_cols))
        return m_entries[i * m_cols + j];
    else 
        return ErrorType::OUT_OF_BOUNDS;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::operator()(
    Index i,
    Index j
) const -> ErrorOr<Value const&>
{
    if ((i < m_rows) && (j < m_cols))
        return m_entries[i * m_cols + j];
    else 
        return ErrorType::OUT_OF_BOUNDS;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::get_dims(
) -> std::pair<Index, Index>
{
    return std::make_pair(m_rows, m_cols);
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::get_dims(
) const -> std::pair<Index, Index> 
{
    return std::make_pair(m_rows, m_cols);
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::begin(
) -> Matrix<Field>::Iterator
{
    auto   indices = std::make_pair<Index, Index>(static_cast<Index>(0), static_cast<Index>(0));
    Value* ptr     = &m_entries[0];
    return { indices, ptr, this };
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::cbegin(
) -> Matrix<Field>::Iterator const&
{
    auto   indices = std::make_pair<Index, Index>(static_cast<Index>(0), static_cast<Index>(0));
    Value* ptr     = &m_entries[0];
    return { indices, ptr, this };
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::end(
) -> Matrix<Field>::Iterator
{
    auto indices = std::make_pair<Index, Index>(static_cast<Index>(m_rows), 
                                                static_cast<Index>(m_cols));
    Value* ptr = &m_entries[m_entries.size() - 1];
    return { indices, ptr, this };
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::cend(
) -> Matrix<Field>::Iterator const&
{
    auto indices = std::make_pair<Index, Index>(static_cast<Index>(m_rows), 
                                                static_cast<Index>(m_cols));
    Value* ptr = &m_entries[m_entries.size() - 1] + 1;
    return { indices, ptr, this };
}

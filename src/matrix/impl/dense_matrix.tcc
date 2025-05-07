#include <utility>
#include <cmath>

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
    Index n{ static_cast<Index>(std::sqrt(entries.size())) };
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
    m_entries = other.entries;
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
    m_entries = std::move(other.entries);
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
) -> Value&
{
    return m_entries[i * m_cols + j];
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::operator()(
    Index i,
    Index j
) const -> Value const&
{
    return m_entries[i * m_cols + j];
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
get_dims(
) -> std::pair<Index, Index>
{
    return std::make_pair(m_rows, m_cols);
}

#include <utility>
#include <cmath>

template<typename Field>
Matrix<Field>::Matrix(
    Index rows,
    Index cols
) : m_entries{ std::move(std::vector<Field>(rows * cols)) }
  , m_rows{ rows }
  , m_cols{ cols }
{
}

template<typename Field>
Matrix<Field>::Matrix(
    std::vector<Value>&& entries
) : m_entries{ std::move(entries) }
{
    Index n{ static_cast<Index>(std::sqrt(entries.size())) };
    m_rows = n;
    m_cols = n;
}

template<typename Field>
Matrix<Field>::Matrix(
    Matrix<Field> const& other
) : m_entries{ other.m_entries }
  , m_rows{ other.m_rows }
  , m_cols{ other.m_cols }
{
}


template<typename Field>
Matrix<Field>::Matrix(
    Matrix<Field>&& other
) noexcept
  : m_entries{ std::move(other.m_entries) }
  , m_rows{ std::move(other.m_rows) }
  , m_cols{ std::move(other.m_cols) }
{
}

template<typename Field>
Matrix<Field>&
Matrix<Field>::operator=(
    Matrix<Field> const& other
)
{
    m_entries = other.entries;
    m_rows    = other.m_rows;
    m_cols    = other.m_cols;
    return *this;
}

template<typename Field>
Matrix<Field>&
Matrix<Field>::operator=(
    Matrix<Field>&& other
)
{
    m_entries = std::move(other.entries);
    m_rows    = std::move(other.m_rows);
    m_cols    = std::move(other.m_cols);
    return *this;
}

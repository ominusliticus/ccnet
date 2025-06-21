#include <utility>
#include <cmath>

// ccnet matrix
#include "matrix/arithmetic.hpp"


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
    m_rows = n;
    m_cols = n;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
Matrix<Field>::Matrix(
    Index rows,
    Index cols,
    Entries&& entries
) : m_entries{ std::move(entries) }
  , m_rows{ rows }
  , m_cols{ cols }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
Matrix<Field>::Matrix(
    Entries const& u,
    Entries const& v
) 
{   
    // If we are dealing with non-complex type, then we have to cast.
    // Currently, standard still distinguish complex floating numbers from others
    m_rows = u.size();
    m_cols = v.size();
    m_entries.reserve(m_rows * m_cols);
    for (Index i{ 0 }; i < m_rows; ++i)
        for (Index j{ 0 }; j < m_cols; ++j)
        {
            if constexpr (std::is_floating_point_v<Field>)
                m_entries[i + j * m_rows] = u[i] * v[j]; 
            else
                m_entries[i + j * m_rows] = u[i] * std::conj(v[j]);
        }
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
        return m_entries[i + j * m_rows];
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
        return m_entries[i + j * m_rows];
    else 
        return ErrorType::OUT_OF_BOUNDS;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::operator[](
    std::pair<Index, Index>&& indices
) -> Value&
{
    auto [i, j] = indices;
    return m_entries[i + j * m_rows];
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::operator[](
    std::pair<Index, Index>&& indices
) const -> Value const&
{
    auto [i, j] = indices;
    return m_entries[i + j * m_rows];
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::eq(
    Matrix<Field> const& other,
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
Matrix<Field>::clone(
) -> Matrix<Field>
{
    Matrix<Field> mat(m_rows, m_cols);
    mat.m_entries = m_entries;
    return mat;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::clone(
) const -> Matrix<Field>
{
    Matrix<Field> mat(m_rows, m_cols);
    mat.m_entries = m_entries;
    return mat;
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
Matrix<Field>::Ident(
    Index dim
) -> Matrix<Value>
{
    Matrix<Value> mat(dim, dim);
    for (Index n{ 0 }; n < dim; ++n)
        mat[{n, n}] = static_cast<Value>(1.0);
    return mat;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename Field>
auto
Matrix<Field>::from_col_major(
    Index rows,
    Index cols,
    Entries&& entries
) -> Matrix<Field>
{
    Matrix<Field> mat(rows, cols);
    for (Index n{ 0 }; n < entries.size(); ++n)
    {
        Index l = n % cols;
        Index k = (n - l) / cols;
        Index i = l * rows + k;
        mat.m_entries[i] = entries[n];
    }
    return mat;
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

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

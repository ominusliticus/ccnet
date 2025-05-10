
#include <cmath>
#include <utility>


template<MatrixConcept Block>
BlockDiagonalMatrix<Block>::BlockDiagonalMatrix(
    Entries&& entries
) : m_entries{ std::move(entries) }
{
    m_dims_list = [](Entries const& entries) -> DimsList {
        DimsList dims_list(entries.size());
        for (Block const& mat : entries)
             dims_list.push_back(mat.get_dims());
        return dims_list;
    }(m_entries);
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
BlockDiagonalMatrix<Block>::BlockDiagonalMatrix(
    BlockDiagonalMatrix<Block> const& other
) : m_entries{ other.m_entries }
  , m_dims_list{ other.m_dims_list }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
BlockDiagonalMatrix<Block>::BlockDiagonalMatrix(
    BlockDiagonalMatrix<Block>&& other
) noexcept
  : m_entries{ std::move(other.m_entries) }
  , m_dims_list{ std::move(other.m_dims_list) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::operator=(
    BlockDiagonalMatrix<Block> const& other

) -> BlockDiagonalMatrix<Block>&
{
    m_entries   = other.entries;
    m_dims_list = other.m_dims_list;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto 
BlockDiagonalMatrix<Block>::operator=(
    BlockDiagonalMatrix<Block>&& other
) -> BlockDiagonalMatrix<Block>&
{
    m_entries   = std::move(other.entries);
    m_dims_list = std::move(other.m_dims_list);
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::operator()(
    Index i,
    Index j
) -> Value&
{
    Index block_index;
    Index rows{ 0 };
    Index cols{ 0 };
    for (auto const&[subrows, subcols] : m_dims_list) 
    {
        rows += subrows;
        cols += subcols;
        if (i <= rows && j <= cols)
            return m_entries[block_index](i - rows + subrows, j - cols + subcols);
        ++block_index;
    }
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::operator()(
    Index i,
    Index j
) const -> Value const&
{
    Index block_index;
    Index rows{ 0 };
    Index cols{ 0 };
    for (auto const&[subrows, subcols] : m_dims_list) 
    {
        rows += subrows;
        cols += subcols;
        if (i <= rows && j <= cols)
            return m_entries[block_index](i - rows + subrows, j - cols + subcols);
        ++block_index;
    }
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::to_dense(
) -> Matrix<Value>
{
    Index rows{ 0 };
    Index cols{ 0 };
    for (auto const& [subrows, subcols] : m_dims_list)
    {
        rows += subrows;
        cols += subcols;
    }
    Matrix<Block> mat(rows, cols);
    for (Index i{ 0 }; i < rows; ++i)
        for (Index j{ 0 }; j < cols; ++j)
            mat(i, j) = *this(i, j);

    return mat;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::get_dims(
) -> std::pair<Index, Index>
{
    auto add_pairs = [](
        std::pair<Index, Index> a, std::pair<Index, Index> b
    ) -> std::pair<Index, Index> {
        return std::make_pair(std::get<0>(a) + std::get<0>(b), std::get<1>(a) + std::get<1>(b));
    };
    auto dim = std::make_pair<Index, Index>(0, 0);
    for (auto const& mat : m_entries)
        dim = add_pair(dim, mat.get_dims());
    return dim;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::get_dims(
) const -> std::pair<Index, Index>
{
    auto add_pairs = [](
        std::pair<Index, Index> a, std::pair<Index, Index> b
    ) -> std::pair<Index, Index> {
        return std::make_pair(std::get<0>(a) + std::get<0>(b), std::get<1>(a) + std::get<1>(b));
    };
    auto dim = std::make_pair<Index, Index>(0, 0);
    for (auto const& mat : m_entries)
        dim = add_pair(dim, mat.get_dims());
    return dim;
}

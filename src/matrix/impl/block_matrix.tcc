
#include <cmath>
#include <utility>


template<MatrixConcept Block>
BlockDiagonalMatrix<Block>::BlockDiagonalMatrix(
    Entries&& entries
) : m_dims_list{}
  , m_entries{ std::move(entries) }
{
    m_dims_list = [](Entries const& entries) -> DimsList {
        DimsList dims_list;
        for (Block const& mat : entries)
             dims_list.push_back(mat.get_dims());
        return dims_list;
    }(m_entries);
    println(m_dims_list.size());
    println(m_entries.size());
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
  : m_dims_list{ std::move(other.m_dims_list) }
  , m_entries{ std::move(other.m_entries) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::operator=(
    BlockDiagonalMatrix<Block> const& other

) -> BlockDiagonalMatrix<Block>&
{
    m_entries   = other.m_entries;
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
    m_entries   = std::move(other.m_entries);
    m_dims_list = std::move(other.m_dims_list);
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::operator()(
    Index i,
    Index j
) -> ErrorOr<Value&>
{
    Index block_index{ 0 };
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
    auto [rows_, cols_] = get_dims();
    if ((i >= rows_) && (j >= cols_)) 
        return ErrorType::OUT_OF_BOUNDS;
    else
        return ErrorType::INDEX_NOT_IN_LIST;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::operator()(
    Index i,
    Index j
) const -> ErrorOr<Value const&>
{
    Index block_index{ 0 };
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
    auto [rows_, cols_] = get_dims();
    if ((i >= rows_) && (j >= cols_)) 
        return ErrorType::OUT_OF_BOUNDS;
    else
        return ErrorType::INDEX_NOT_IN_LIST;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::operator[](
    std::pair<Index, Index>&& indices
) -> Value&
{
    Index block_index{};
    Index rows{ 0 };
    Index cols{ 0 };
    auto [i, j] = indices;
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
BlockDiagonalMatrix<Block>::operator[](
    std::pair<Index, Index>&& indices
) const -> Value const&
{
    Index block_index{};
    Index rows{ 0 };
    Index cols{ 0 };
    auto [i, j] = indices;
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
BlockDiagonalMatrix<Block>::eq(
    BlockDiagonalMatrix<Block> const& other,
    double tol
) -> ErrorOr<bool>
{
    auto const [orows, ocols] = other.get_dims();
    auto const [mrows, mcols] = get_dims();
    if (!((orows == mrows) && (ocols == mcols))) return ErrorType::INCOMPATIBLE_DIMENSIONS;

    bool is_same = true;
    for (Index n{ 0 }; n < m_entries.size(); ++n)
        is_same &= TRY(m_entries[n].eq(other.m_entries[n], tol));
    return is_same;
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
    println(rows, cols);
    Matrix<Value> mat(rows, cols);
    rows = cols = 0;
    for (auto& block : m_entries)
    {
        println(block);
        for (auto const& itr : block)
        {
            auto const& [i, j] = *itr.indices;
            println(i, j, *itr.value);
            mat[{rows + i, cols + j}]= *itr.value;
        }
        auto const& [subrows, subcols] = block.get_dims();
        rows += subrows;
        cols += subcols;
    }

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
        dim = add_pairs(dim, mat.get_dims());
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
        dim = add_pairs(dim, mat.get_dims());
    return dim;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::begin(
) -> BlockDiagonalMatrix<Block>::Iterator 
{
    auto   indices = std::make_pair<Index, Index>(0, 0);
    Value* value   = &m_entries[0](0, 0);
    return { indices, value, 0, this};
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::cbegin(
) -> BlockDiagonalMatrix<Block>::Iterator const&
{
    auto   indices = std::make_pair<Index, Index>(0, 0);
    Value* value   = &m_entries[0](0, 0);
    return { indices, value, 0, this };
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::end(
) -> BlockDiagonalMatrix<Block>::Iterator 
{
    auto   indices = get_dims();
    Value* value   = (*m_entries.end()).end().value;
    return { indices, value, m_entries.size(), this };
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<MatrixConcept Block>
auto
BlockDiagonalMatrix<Block>::cend(
) -> BlockDiagonalMatrix<Block>::Iterator const&
{
    auto   indices = get_dims();
    Value* value   = (*m_entries.end()).end().value;
    return { indices, value, m_entries.size(), this };
}

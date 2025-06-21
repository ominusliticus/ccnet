#pragma once

template<typename MatrixType>
concept MatrixConcept = requires (MatrixType mat) {
    typename MatrixType::Value;
    typename MatrixType::Index;

    // Require that operator() is overloaded to take two arguments of type Index
    mat(typename MatrixType::Index(), typename MatrixType::Index());
    // The () is necessary to instantiate the dependent-name MatrixType::Index as a type.
    // Hence, why we also add typename, since it is a templated type
};

// Matrix Printing
template<typename OStream, MatrixConcept MatrixType>
auto
operator<<(
    OStream& ostream,
    MatrixType const& mat
) -> OStream& 
{
    using Index = typename MatrixType::Index;
    auto [rows, cols] = mat.get_dims();
    for (Index i{ 0 }; i < rows; ++i)
    {
        for (Index j{ 0 }; j < cols; ++j)
            ostream << '\t' << mat(i, j).value() << " ";
        ostream << '\n';
    }
    return ostream;
}


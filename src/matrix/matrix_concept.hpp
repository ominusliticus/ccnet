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

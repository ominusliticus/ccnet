#pragma once

template<typename MatrixType>
concept MatrixConcept = requires {
    typename MatrixType::Value;
};

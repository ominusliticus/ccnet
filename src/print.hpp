#pragma once

// STL
#include <iostream>

// For prining matrices
#include "matrix/matrix_concept.hpp"

template<typename...Args>
auto
print(
    Args&&... args
) -> void
{
    ((std::cout << std::forward<Args>(args) << " "), ...);
}

template<typename...Args>
auto
println(
    Args&&... args
) -> void
{
    ((std::cout << std::forward<Args>(args) << " "), ...);
    std::cout << '\n';
}

#pragma once

#include <iostream>

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

// STL
#include <complex>
#include <string>
#include <vector>

// CCNet
#include "print.hpp"
#include "version.hpp"

// matrix
#include "matrix/dense_matrix.hpp"
#include "matrix/block_matrix.hpp"

auto 
version_string(
) -> std::string
{
    std::string major{ CCNet_VERSION_MAJOR };
    std::string minor{ CCNet_VERSION_MINOR };
    return "v" + major + "." + minor;
}

auto
banner(
) -> void
{
    println("CCNet: Chalker-Coddington Network");
    println("Version:", version_string());
}


auto
main(
    [[maybe_unused]] int    argc,
    [[maybe_unused]] char** argv
) -> int
{
    banner();
    println("Hello World!");

    using Field = std::complex<double>;
    std::vector<Field> v{{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0}};
    Matrix<Field>      mat(std::move(v));
    println(std::get<0>(mat.get_dims()), std::get<1>(mat.get_dims()));
    for (Matrix<Field>::Index i{ 0 }; i < std::get<0>(mat.get_dims()); ++i)
    {
        print("[ ");
        for (Matrix<Field>::Index j{ 0 }; j < std::get<1>(mat.get_dims()); ++j)
            print(mat(i, j), ",");
        println("]");
    }
    BlockDiagonalMatrix<Matrix<Field>> block_mat({mat});
    return 0;
}

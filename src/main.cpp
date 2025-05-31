// STL
#include <complex>
#include <string>
#include <vector>

// Util
#include "util/error.hpp"
#include "util/try.hpp"

// CCNet
#include "print.hpp"
#include "version.hpp"

// matrix
#include "matrix/arithmetic.hpp"
#include "matrix/dense_matrix.hpp"
#include "matrix/block_matrix.hpp"

// Function prototypes
std::string version_string();
void        banner();

ErrorOr<void> trivial() { return {}; }

auto
main(
    [[maybe_unused]] int    argc,
    [[maybe_unused]] char** argv
) -> int
{
    banner();
    println("Hello World!");

    using Field = std::complex<double>;
    std::vector<Field> v{{1.0, 0.0}, {2.0, 0.0}, {3.0, 0.0}, {4.0, 0.0}};
    Matrix<Field>      mat(std::move(v));
    println(std::get<0>(mat.get_dims()), std::get<1>(mat.get_dims()));
    for (Matrix<Field>::Index i{ 0 }; i < std::get<0>(mat.get_dims()); ++i)
    {
        print("[ ");
        for (Matrix<Field>::Index j{ 0 }; j < std::get<1>(mat.get_dims()); ++j)
        {
            auto value = TRY_MAIN(mat(i, j));
            print(value, ",");
        }
        println("]");
    }
    BlockDiagonalMatrix<Matrix<Field>> block_mat({mat});
    [[maybe_unused]] auto triv = TRY_MAIN(trivial());

    auto mat_prod = (mat * mat).value();
    for (Matrix<Field>::Index i{ 0 }; i < std::get<0>(mat.get_dims()); ++i)
    {
        print("[ ");
        for (Matrix<Field>::Index j{ 0 }; j < std::get<1>(mat.get_dims()); ++j)
        {
            auto value = TRY_MAIN(mat_prod(i, j));
            print(value, ",");
        }
        println("]");
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Prototyped function implementations
///

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


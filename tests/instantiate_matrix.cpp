// STL
#include <cassert>
#include <complex>
#include <vector>
// CCNet
#include "matrix/dense_matrix.hpp"

// TODO: Need to really build a testing library that will sit untop of the CTest library
//       Largely, I want to build a project that has minimal third-party dependencies.

template<typename Field>
auto
instantiate_matrix(
) -> void
{
    // dense matrices
    {
        Matrix<Field> m(10, 10);
        assert(m(3, 3) == static_cast<Field>(0.0));

        Matrix<Field> m2(std::move(m));
        assert(m2(4, 4) == static_cast<Field>(0.0));

        Matrix<Field> m3 = std::move(m2);
        using Index = typename Matrix<Field>::Index;
        assert((m3.get_dims() == std::make_pair<Index, Index>(10, 10)));
    }

    // sparse matrices
    {

    }

    // block matrices
    {

    }
}

template<typename Field>
auto
instantiate_matrix(
    std::vector<Field>&& v
) -> void
{
    // dense matrices
    {
        Matrix<Field> m(std::move(v));
        assert(m(0, 0) == static_cast<Field>(1.0));

        Matrix<Field> m2(std::move(m));
        assert(m2(1, 1) == static_cast<Field>(4.0));

        Matrix<Field> m3 = std::move(m2);
        using Index = typename Matrix<Field>::Index;
        assert((m3.get_dims() == std::make_pair<Index, Index>(2, 2)));
    }

    // sparse matrices
    {

    }

    // block matrices
    {

    }
}

auto
main(
) -> int
{
    // float test
    instantiate_matrix<float>();
    instantiate_matrix<float>(std::vector<float>{1.0f, 2.0f, 3.0f, 4.0f});
    
    // double test
    instantiate_matrix<double>();
    instantiate_matrix<double>(std::vector<double>{1.0, 2.0, 3.0, 4.0});

    // complex test
    using Field = std::complex<double>;
    instantiate_matrix<Field>();
    instantiate_matrix<Field>(std::vector<Field>{
        {1.0, 0.0}, {2.0, 0.0}, {3.0, 0.0}, {4.0, 0.0}
    });
    return 0;
}

// STL
#include <vector>
#include <complex>
// CCNet
#include "matrix/dense_matrix.hpp"

// TODO: Need to really build a testing library that will sit untop of the CTest library
//       Largely, I want to build a project that has minimal third-party dependencies.

template<typename Field>
auto
instantiate_matrix(
) -> void
{
    Matrix<Field> m(10, 10);
    Matrix<Field> m2(std::move(m));
    Matrix<Field> m3 = std::move(m2);
    (void)m3;
}

template<typename Field>
auto
instantiate_matrix(
    std::vector<Field>&& v
) -> void
{
    Matrix<Field> m(std::move(v));
    Matrix<Field> m2(std::move(m));
    Matrix<Field> m3 = std::move(m2);
    (void)m3;
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
    using complex = std::complex<double>;
    instantiate_matrix<complex>();
    instantiate_matrix<complex>(std::vector<complex>{
        {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0}
    });
}

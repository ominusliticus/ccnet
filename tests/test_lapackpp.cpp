#include <lapack.hh>

int main() {
    std::complex<double> mat[3 * 3] = {
        { 1.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 },
        { 0.0, 0.0 }, { 1.0, 0.0 }, { 0.0, 0.0 },
        { 0.0, 0.0 }, { 0.0, 0.0 }, { 1.0, 0.0 }
    };
    int64_t pivot[3] = { 1, 2, 3 };
    int64_t return_code = lapack::getrf2(3, 3, mat, 3, pivot);
    return return_code;
}

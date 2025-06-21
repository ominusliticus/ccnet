#include <lapack.hh>

int main() {
    float a[] = { 12.0f, 6.0f, -4.0f, -51.0f, 167.0f, 24.0f, 4.0f, -68.0f, -41.0f };
    float t[3];
    int64_t return_code = lapack::geqr2(3, 3, a, 3, t);
    std::cout << return_code << "\n";
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
            std::cout << "\t" << a[i + 3 * j] << " ";
         std::cout << "\n";
    }
    return return_code;
}

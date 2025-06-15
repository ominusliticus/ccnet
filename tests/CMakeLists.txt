include(CTest)

# =========================================================
# TEST: Instantiate Matrix
add_executable(
    instantiate_matrix
    instantiate_matrix.cpp
)
target_include_directories(
    instantiate_matrix
    PUBLIC
    ${CCNet_SRC_DIR}
    "${CCNet_SOURCE_DIR}/third_party/installs/include"
    "$ENV{HOME}/intel/oneapi/2025.1/include"
)
add_test(
    NAME InstantiateMatrix
    COMMAND instantiate_matrix
)
# =========================================================


# =========================================================
# TEST: Instantiate Matrix
add_executable(
    block_matrix
    block_matrix.cpp
)
target_include_directories(
    block_matrix
    PUBLIC
    ${CCNet_SRC_DIR}
    "${CCNet_SOURCE_DIR}/third_party/installs/include"
    "$ENV{HOME}/intel/oneapi/2025.1/include"
)
add_test(
    NAME BlockMatrix
    COMMAND block_matrix
)
# =========================================================


# =========================================================
# TEST: Run LAPACK++
add_executable(
    test_lapackpp
    test_lapackpp.cpp
)
target_include_directories(
    test_lapackpp
    PUBLIC
    ${CCNet_SRC_DIR}
)
target_include_directories(
    test_lapackpp
    PUBLIC
    ${CCNet_SRC_DIR}
    "${CCNet_SOURCE_DIR}/third_party/installs/include"
    "$ENV{HOME}/intel/oneapi/2025.1/include"
)
target_link_libraries(
    test_lapackpp
    PUBLIC
    blaspp
    lapackpp
    $<LINK_ONLY:MKL::MKL>
)
add_test(
    NAME CompileLAPACK++
    COMMAND test_lapackpp
)
# =========================================================


# =========================================================
# TEST: QR Decomposition
add_executable(
    test_qr_decomposition
    test_qr_decomposition.cpp
)
target_include_directories(
    test_qr_decomposition
    PUBLIC
    ${CCNet_SRC_DIR}
)
target_include_directories(
    test_qr_decomposition
    PUBLIC
    ${CCNet_SRC_DIR}
    "${CCNet_SOURCE_DIR}/third_party/installs/include"
    "$ENV{HOME}/intel/oneapi/2025.1/include"
)
target_link_libraries(
    test_qr_decomposition
    PUBLIC
    blaspp
    lapackpp
    $<LINK_ONLY:MKL::MKL>
)
target_sources(
    test_qr_decomposition
    PUBLIC
    ${CCNet_SOURCE_FILES}
)
add_test(
    NAME QRDecomposition
    COMMAND test_qr_decomposition
)
# =========================================================

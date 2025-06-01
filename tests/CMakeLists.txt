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
)
add_test(
    NAME BlockMatrix
    COMMAND block_matrix
)
# =========================================================

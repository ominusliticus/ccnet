include(CTest)

# =========================================================
# TEST: Instantiate Matrix
add_executable(
    instantiate_matrix
    instantiate_matrix.cpp
)
target_include_directories(
    instantiate_matrix
    PRIVATE
    ${CCNet_SRC_DIR}
)
add_test(
    NAME InstantiateMatrix
    COMMAND instantiate_matrix
)
# =========================================================

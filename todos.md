Keeping track of my thoughts here, to avoid premature optimizations.

# Important design considerations

- Currently, the access operatores `operator()(Index i, Index j)` do not perform bounds checking.
  This operations can be marked noexcept and promoted to monads (return optionals).
- Need to support building no square matrices in `dense_matrix.hpp`
- Should matrix operations be optional in general, since incorrect dimensions are possible?
  - For now, I am implementing the simplest error class I can image.
  - I am considering adding `error_or` and `value_or` methods as well.


# Reach goals that arise as I program

- It would be good to build a testing library untop of CTest (a little like Google's testingn 
  library), that makes unit testing individual functions more fun. 
  An idea is to create macros that populate a translation unit with different test, and then 
  during the compilation process, call the compiled executed a different name (and store everything
  in a hidden directory so that user doesn't have to see it, or a temp directory and just recompile
  the tests every time).

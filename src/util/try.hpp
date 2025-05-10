#pragma once

// macro to bubble errors to int main function
#define TRY(result)                                                                               \
  ({                                                                                              \
      auto&& error_or = result;                                                                   \
      if (error_or.is_error())                                                                    \
      {                                                                                           \
          printf("Bubbling error from function: %s\n", #result);                                  \
          return error_or.error();                                                                \
    }                                                                                             \
        error_or.release();                                                                       \
  })

// macro called in int main to handle any functions that can return erro
#define TRY_MAIN_(result, line)                                                                   \
  ({                                                                                              \
      auto&& error_or = result;                                                                   \
      if (error_or.is_error())                                                                    \
      {                                                                                           \
          printf("Exiting with error: %s\n", strerror(error_or.error().value()));                 \
          printf("Program failed at line %d\n", line);                                            \
          return 0;                                                                               \
      }                                                                                           \
      error_or.release();                                                                         \
  })

#define TRY_MAIN(result) TRY_MAIN_(result, __LINE__)

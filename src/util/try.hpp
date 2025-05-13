#pragma once

// macro to bubble errors to int main function
#define TRY(result)                                                                               \
  ({                                                                                              \
      auto&& error_or = result;                                                                   \
      if (error_or.is_error())                                                                    \
      {                                                                                           \
          print("Bubbling error from function: %s\n", #result);                                   \
          return error_or.error();                                                                \
    }                                                                                             \
        error_or.value();                                                                         \
  })

// macro called in int main to handle any functions that can return erro
#define TRY_MAIN_(result, line)                                                                   \
  ({                                                                                              \
      auto&& error_or = result;                                                                   \
      if (error_or.is_error())                                                                    \
      {                                                                                           \
          print("Exiting with error: %s\n", error_to_str(error_or.error()));                      \
          print("Program failed at line %d\n", line);                                             \
          return 0;                                                                               \
      }                                                                                           \
      error_or.value();                                                                           \
  })

#define TRY_MAIN(result) TRY_MAIN_(result, __LINE__)

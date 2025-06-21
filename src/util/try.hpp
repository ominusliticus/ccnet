#pragma once

// macro to bubble errors to int main function
#define TRY(result)                                                                               \
  ({                                                                                              \
      auto&& error_or = result;                                                                   \
      if (error_or.is_error())                                                                    \
      {                                                                                           \
          println("Bubbling error from expression: ", #result);                                   \
          println("At", __FILE__, __LINE__, ":", __PRETTY_FUNCTION__);                            \
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
          println("Exiting with error: ", error_to_str(error_or.error()));                        \
          println("Program failed at line ", __FILE__, line);                                     \
          return -999;                                                                            \
      }                                                                                           \
      error_or.value();                                                                           \
  })

#define TRY_MAIN(result) TRY_MAIN_(result, __LINE__)

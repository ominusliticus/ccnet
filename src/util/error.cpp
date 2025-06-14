#include "error.h"
#include "util/error.hpp"

#include <string>

auto
error_to_str(
    ErrorType error
)-> std::string
{
    switch (error) {
        case ErrorType::NO_ERRORS: return "no errors";
        case ErrorType::OUT_OF_BOUNDS: return "Index out of bounds";
        case ErrorType::INDEX_NOT_IN_LIST: return "Indices not found in index list";
        case ErrorType::INCOMPATIBLE_DIMENSIONS: return "Matrix dimensions mismatch";
        case ErrorType::SINGULAR_MATRIX: return "Matrix is singular";
        case ErrorType::FACTORIZATION_FAILED: return "Factorization failed";
        default: return "unknown error";
    }
}


ErrorOr<void>::ErrorOr(
    Empty value
)
  : m_value{ value }
  , m_error{ ErrorType::NO_ERRORS }
  , m_is_error{ false }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

ErrorOr<void>::ErrorOr(
    ErrorType error
)
  : m_value{ Empty{} }
  , m_error{ error }
  , m_is_error{ true }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

ErrorOr<void>::ErrorOr(
    ErrorOr<void> const& other
)
  : m_value{ other.value() }
  , m_error{ other.error() }
  , m_is_error{ other.m_is_error }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

ErrorOr<void>::ErrorOr(
    ErrorOr<void>&& other
) noexcept
  : m_value{ std::move(other.m_value) }
  , m_error{ std::move(other.m_error) }
  , m_is_error{ std::move(other.m_is_error) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

auto
ErrorOr<void>::operator=(
    ErrorOr<void> const& other
) -> ErrorOr<void>& 
{
    m_value = other.m_value;
    m_error = other.m_error;
    m_is_error = other.m_is_error;
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

auto
ErrorOr<void>::operator=(
    ErrorOr<void>&& other
) -> ErrorOr<void>& 
{
    m_value = std::move(other.m_value);
    m_error = std::move(other.m_error);
    m_is_error = std::move(other.m_is_error);
    return *this;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

auto
ErrorOr<void>::value(
) -> Empty& 
{
    return m_value;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

auto
ErrorOr<void>::value(
) const -> Empty const& 
{
    return m_value;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

auto
ErrorOr<void>::error(
) -> ErrorType 
{
    return m_error;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

auto
ErrorOr<void>::error(
) const -> ErrorType const& 
{
    return m_error;
}

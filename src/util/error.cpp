#include "error.h"

template<>
ErrorOr<void>::ErrorOr(
    void value
)
  : m_value{ value }
  , m_error{ ErrorType::NO_ERRORS }
  , m_is_error{ false }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<>
ErrorOr<void>::ErrorOr(
    ErrorType error
)
  : m_value{ Empty{} }
  , m_error{ error }
  , m_is_error{ true }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<>
ErrorOr<void>::ErrorOr(
    ErrorOr<void> const& other
)
  : m_value{ other.value }
  , m_error{ other.error }
  , m_is_error{ other.m_is_error }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<>
ErrorOr<void>::ErrorOr(
    ErrorOr<void>&& other
) noexcept
  : m_value{ std::move(other.m_value) }
  , m_error{ std::move(other.m_error) }
  , m_is_error{ std::move(other.m_is_error) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<>
auto
ErrorOr<void>::operator=(
    ErrorOr<void> const& other
) -> ErrorOr<void>& 
{
    m_value = other.m_value;
    m_error = other.m_error;
    m_is_error = other.m_is_error;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<>
auto
ErrorOr<void>::operator=(
    ErrorOr<void>&& other
) -> ErrorOr<void>& 
{
    m_value = std::move(other.m_value);
    m_error = std::move(other.m_error);
    m_is_error = std::move(other.m_is_error);
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<>
auto
ErrorOr<void>::value(
) -> Empty& 
{
    return m_value;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<>
auto
ErrorOr<void>::value(
) -> Empty const& 
{
    return m_value;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<>
auto
ErrorOr<void>::error(
) -> ErrorType& 
{
    return m_error;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<>
auto
ErrorOr<void>::error(
) -> ErrorType const& 
{
    return m_error;
}

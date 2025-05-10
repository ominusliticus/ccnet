// Line intentionally commented out

template<typename T>
ErrorOr<T>::ErrorOr(
    T value
)
  : m_value{ value }
  , m_error{ ErrorType::NO_ERRORS }
  , m_is_error{ false }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename T>
ErrorOr<T>::ErrorOr(
    ErrorType error
)
  : m_value{ Empty{} }
  , m_error{ error }
  , m_is_error{ true }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename T>
ErrorOr<T>::ErrorOr(
    ErrorOr<T> const& other
)
  : m_value{ other.value }
  , m_error{ other.error }
  , m_is_error{ other.m_is_error }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename T>
ErrorOr<T>::ErrorOr(
    ErrorOr<T>&& other
) noexcept
  : m_value{ std::move(other.m_value) }
  , m_error{ std::move(other.m_error) }
  , m_is_error{ std::move(other.m_is_error) }
{
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename T>
auto
ErrorOr<T>::operator=(
    ErrorOr<T> const& other
) -> ErrorOr<T>& 
{
    m_value = other.m_value;
    m_error = other.m_error;
    m_is_error = other.m_is_error;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename T>
auto
ErrorOr<T>::operator=(
    ErrorOr<T>&& other
) -> ErrorOr<T>& 
{
    m_value = std::move(other.m_value);
    m_error = std::move(other.m_error);
    m_is_error = std::move(other.m_is_error);
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename T>
auto
ErrorOr<T>::value(
) -> T& 
{
    return m_value;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename T>
auto
ErrorOr<T>::value(
) const -> T const& 
{
    return m_value;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename T>
auto
ErrorOr<T>::error(
) -> ErrorType& 
{
    return m_error;
}

// .....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....ooo0ooo.....

template<typename T>
auto
ErrorOr<T>::error(
) const -> ErrorType const& 
{
    return m_error;
}

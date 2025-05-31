#pragma once

#include <type_traits>
#include <cstdint>
#include <string>

enum class ErrorType : std::size_t {
    // Matrix Operations
    NO_ERRORS = 0,
    OUT_OF_BOUNDS,
    INDEX_NOT_IN_LIST,
    INCOMPATIBLE_DIMENSIONS,
    SINGULAR_MATRIX
};

std::string error_to_str(ErrorType error);

struct Empty {};

template<typename T>
class [[nodiscard]] ErrorOr {
public:
    using ValueType = std::remove_reference_t<T>;

    // Value constructors
    ErrorOr() = default;
    ErrorOr(T value);
    ErrorOr(ErrorType error);

    // Copy and move operations
    ErrorOr(ErrorOr const& other);
    ErrorOr(ErrorOr&& other) noexcept;

    ErrorOr& operator=(ErrorOr const& other);
    ErrorOr& operator=(ErrorOr&& other);

    // Factories
    template<typename U>
    static ErrorOr<U> from_value(U&& value) requires std::is_same_v<T, U>;

    template<typename U>
    static ErrorOr<U> from_error(ErrorType error) requires std::is_same_v<T, U>;

    // Accessors
    ValueType&       value();
    ValueType const& value() const;
    ErrorType&       error();
    ErrorType const& error() const;

    // For boolean logic
    explicit operator bool() const { return !m_is_error; }
    bool              is_error() const { return m_is_error; }
private:
    ValueType m_value;
    ErrorType m_error;
    bool      m_is_error;
};

template<>
class [[nodiscard]] ErrorOr<void> {
public:
    // Value constructors
    ErrorOr() = default;
    ErrorOr(Empty value);
    ErrorOr(ErrorType error);

    // Copy and move operations
    ErrorOr(ErrorOr const& other);
    ErrorOr(ErrorOr&& other) noexcept;

    ErrorOr& operator=(ErrorOr const& other);
    ErrorOr& operator=(ErrorOr&& other);

    // Factories
    static ErrorOr<void> from_error(ErrorType error);

    // Accessors
    Empty&           value();
    Empty const&     value() const;
    ErrorType        error();
    ErrorType const& error() const;

    // For boolean logic
    explicit operator bool() const { return !m_is_error; }
    bool              is_error() const { return m_is_error; }
private:
    Empty     m_value;
    ErrorType m_error;
    bool      m_is_error;
};

#include "impl/error.tcc"

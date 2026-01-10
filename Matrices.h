#pragma once
#include "TemplateConstraint.h"
#include <print>
#include <array>
#include <ranges>
#include <algorithm>
namespace LinAlg
{
    template<uint8_t size, Numeric Number>
    class Matrix
    {
    public:
        Matrix() noexcept = default;
        Matrix(const Matrix& other) noexcept = default;
        Matrix(Matrix&& other) noexcept = default;
        Matrix& operator=(const Matrix& other) noexcept = default;
        Matrix& operator=(Matrix&& other) noexcept = default;
        ~Matrix() = default;
        explicit Matrix(std::initializer_list<std::initializer_list<Number>> init)
        {
            auto input_view = init | std::views::join | std::views::take(size * size);
            std::ranges::copy(input_view, this->flat().begin());
        }
        explicit Matrix(Number scalar) noexcept
        {
            std::ranges::fill(this->flat(), scalar);
        }
        friend void printMatrix(const Matrix& mat) noexcept
        {
            std::println("Matrix {}x{}: ", size, size);
            for (const auto& row : mat.m_matrixArr)
            {
                std::println("{}", row); // much better
            }
            std::println();
        }
    public:
        friend constexpr auto operator+(const Matrix& other, const Matrix& other2) noexcept -> Matrix
        {
            Matrix result;
            std::ranges::transform(
                other.flat(),           // Input Range 1: The flattened Left-Hand Side matrix.
                other2.flat(),          // Input Range 2: The flattened Right-Hand Side matrix.
                result.flat().begin(), // Output Iterator: Where to start writing the results.
                std::plus{}          // The Operation: A standard functor that performs addition (x + y).
            );
            return result;
        }
        constexpr auto operator+=(this auto& self,const Matrix& other) noexcept -> Matrix&
        {
            std::ranges::transform(
                self.flat(),           // Input Range 1: The flattened Left-Hand Side matrix.
                other.flat(),          // Input Range 2: The flattened Right-Hand Side matrix.
                self.flat().begin(), // Output Iterator: Where to start writing the results.
                std::plus{}          // The Operation: A standard functor that performs addition (x + y).
            );
            return self;
        }
        constexpr auto operator+(this auto& self, Number scalar) noexcept -> Matrix
        {
            Matrix result;
            std::ranges::transform(
                self.flat(),
                result.flat().begin(),
                [scalar](Number n)
                {
                    // We return the sum, which 'transform' writes into the Output location.
                    return n + scalar;
                }
            );
            return result;
        }
        constexpr auto operator+=(this auto& self, Number scalar) noexcept -> Matrix&
        {
            std::ranges::transform(
                self.flat(),
                self.flat().begin(),
                [scalar](Number n)
                {
                    return n + scalar;
                }
            );
            return self;
        }
    public:
        friend constexpr auto operator-(const Matrix& other, const Matrix& other2) noexcept -> Matrix
        {
            Matrix result;
            std::ranges::transform(
                other.flat(),           // Input Range 1: The flattened Left-Hand Side matrix.
                other2.flat(),          // Input Range 2: The flattened Right-Hand Side matrix.
                result.flat().begin(), // Output Iterator: Where to start writing the results.
                std::minus{}          // The Operation: A standard functor that performs addition (x + y).
            );
            return result;
        }
        constexpr auto operator-=(this auto& self,const Matrix& other) noexcept -> Matrix&
        {
            std::ranges::transform(
                self.flat(),           // Input Range 1: The flattened Left-Hand Side matrix.
                other.flat(),          // Input Range 2: The flattened Right-Hand Side matrix.
                self.flat().begin(), // Output Iterator: Where to start writing the results.
                std::minus{}          // The Operation: A standard functor that performs addition (x + y).
            );
            return self;
        }
        constexpr auto operator-(this auto& self, Number scalar) noexcept -> Matrix
        {
            // Left-Hand Side = LHS, Right-Hand Size = RHS
            Matrix result;
            std::ranges::transform(
                self.flat(),
                result.flat().begin(),
                [scalar](Number n)
                {
                    // We return the sum, which 'transform' writes into the Output location.
                    return n - scalar;
                }
            );
            return result;
        }
        constexpr auto operator-=(this auto& self, Number scalar) noexcept -> Matrix&
        {
            std::ranges::transform(
                self.flat(),
                self.flat().begin(),
                [scalar](Number n)
                {
                    return n - scalar;
                }
            );
            return self;
        }
    public:
        constexpr auto operator*(this auto& self, Number scalar) noexcept -> Matrix
        {
            // Left-Hand Side = LHS, Right-Hand Size = RHS
            Matrix result;
            std::ranges::transform(
                self.flat(),
                result.flat().begin(),
                [scalar](Number n)
                {
                    // We return the sum, which 'transform' writes into the Output location.
                    return n * scalar;
                }
            );
            return result;
        }
        constexpr auto operator*=(this auto& self, Number scalar) noexcept -> Matrix&
        {
            std::ranges::transform(
                self.flat(),
                self.flat().begin(),
                [scalar](Number n)
                {
                    return n * scalar;
                }
            );
            return self;
        }
    public:
        friend void roundOff(Matrix& mat, uint8_t decimalDigit) noexcept
        {
            auto TenPower = TenRaise(decimalDigit);
            std::ranges::transform(
                mat.m_matrixArr | std::views::join,
                (mat.m_matrixArr | std::views::join).begin(),
                [TenPower](Number n)
                {
                    return std::round(n * TenPower) / TenPower;
                }
            );
        }
    private:
        constexpr auto flat(this auto&& self) {return self.m_matrixArr | std::views::join;};
        // "std::views::join" treats the 2D array as a single continuous 1D sequence.
        // Flattened means
        // Row1: [1,2,3], Row2: [4,5,6]
        // Sequence: [1,2,3,4,5,6]
        std::array<std::array<Number, size>, size> m_matrixArr{T_zero_init<Number>()};
        static constexpr std::pair<uint8_t, uint8_t> MATRIX_SIZES_LIMITS{2,5};
        static_assert(size >= MATRIX_SIZES_LIMITS.first && size <= MATRIX_SIZES_LIMITS.second, "Not Valid Size!");

    };

    using Mat2u8        =  Matrix<2, uint8_t>;
    using Mat2u16       =  Matrix<2, uint16_t>;
    using Mat2u32       =  Matrix<2, uint32_t>;
    using Mat2u64       =  Matrix<2, uint64_t>;
    using Mat2s         =  Matrix<2, short>;
    using Mat2i         =  Matrix<2, int>;
    using Mat2l         =  Matrix<2, long>;
    using Mat2st        =  Matrix<2, size_t>;
    using Mat2f         =  Matrix<2, float>;
    using Mat2d         =  Matrix<2, double>;

    using Mat3u8        =  Matrix<3, uint8_t>;
    using Mat3u16       =  Matrix<3, uint16_t>;
    using Mat3u32       =  Matrix<3, uint32_t>;
    using Mat3u64       =  Matrix<3, uint64_t>;
    using Mat3s         =  Matrix<3, short>;
    using Mat3i         =  Matrix<3, int>;
    using Mat3l         =  Matrix<3, long>;
    using Mat3st        =  Matrix<3, size_t>;
    using Mat3f         =  Matrix<3, float>;
    using Mat3d         =  Matrix<3, double>;

    using Mat4u8        =  Matrix<4, uint8_t>;
    using Mat4u16       =  Matrix<4, uint16_t>;
    using Mat4u32       =  Matrix<4, uint32_t>;
    using Mat4u64       =  Matrix<4, uint64_t>;
    using Mat4s         =  Matrix<4, short>;
    using Mat4i         =  Matrix<4, int>;
    using Mat4l         =  Matrix<4, long>;
    using Mat4st        =  Matrix<4, size_t>;
    using Mat4f         =  Matrix<4, float>;
    using Mat4d         =  Matrix<4, double>;

    using Mat5u8        =  Matrix<5, uint8_t>;
    using Mat5u16       =  Matrix<5, uint16_t>;
    using Mat5u32       =  Matrix<5, uint32_t>;
    using Mat5u64       =  Matrix<5, uint64_t>;
    using Mat5s         =  Matrix<5, short>;
    using Mat5i         =  Matrix<5, int>;
    using Mat5l         =  Matrix<5, long>;
    using Mat5st        =  Matrix<5, size_t>;
    using Mat5f         =  Matrix<5, float>;
    using Mat5d         =  Matrix<5, double>;
}

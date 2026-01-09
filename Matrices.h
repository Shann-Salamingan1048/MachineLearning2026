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

        explicit Matrix(Number scalar) noexcept
        {
            std::ranges::fill(m_matrixArr | std::views::join, scalar);
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
        Matrix operator+(const Matrix& other) noexcept
        {
            // Left-Hand Side = LHS, Right-Hand Size = RHS
            Matrix result;
            // Flattened means
            // Row1: [1,2,3], Row2: [4,5,6]
            // Sequence: [1,2,3,4,5,6]

            // Create a "view" of the current object's (LHS) 2D array.
            // "std::views::join" treats the 2D array as a single continuous 1D sequence.
            auto self_flat = m_matrixArr | std::views::join;
            // Create a flattened view of the "other" object's (RHS) 2D array.
            auto other_flat = other.m_matrixArr | std::views::join;

            // Create a flattened view of the "result" matrix so we can write to it linearly.
            auto result_flat = result.m_matrixArr | std::views::join;
            // Perform the addition using the standard library algorithm.
            std::ranges::transform(
                self_flat,           // Input Range 1: The flattened Left-Hand Side matrix.
                other_flat,          // Input Range 2: The flattened Right-Hand Side matrix.
                result_flat.begin(), // Output Iterator: Where to start writing the results.
                std::plus{}          // The Operation: A standard functor that performs addition (x + y).
            );
            return result;
        }
        Matrix operator+=(const Matrix& other) noexcept
        {
            auto self_flat = m_matrixArr | std::views::join;
            auto other_flat = other.m_matrixArr | std::views::join;
            //auto result_flat = m_matrixArr | std::views::join;
            // Perform the addition using the standard library algorithm.
            std::ranges::transform(
                self_flat,           // Input Range 1: The flattened Left-Hand Side matrix.
                other_flat,          // Input Range 2: The flattened Right-Hand Side matrix.
                self_flat.begin(), // Output Iterator: Where to start writing the results.
                std::plus{}          // The Operation: A standard functor that performs addition (x + y).
            );
            return *this;
        }
        Matrix operator+(Number scalar) noexcept
        {
            // Left-Hand Side = LHS, Right-Hand Size = RHS
            Matrix result;
            std::ranges::transform(
                // 4. THE INPUT (Source)
                // 'm_matrixArr' is 2D (array inside array).
                // The pipe '|' passes the array into 'views::join'.
                // 'join' creates a virtual "view" that looks like a flat 1D line of numbers.
                // It allows us to read [row1_col1, row1_col2, row2_col1...] sequentially.
                m_matrixArr | std::views::join,
                // 5. THE OUTPUT (Destination Iterator)
                // We need to tell 'transform' where to START writing in the 'result' matrix.
                // We must also 'join' the result matrix so the structure matches the input.
                // .begin() gives us the pointer to the very first slot of that flattened view.
                (result.m_matrixArr | std::views::join).begin(),

                // 6. THE OPERATION (Lambda)
                // [scalar]: We "capture" the variable 'scalar' from the function arguments
                //           so we can use it inside this small lambda function.
                // (Number n): 'transform' passes the current number from the Input here.
                [scalar](Number n)
                {
                    // We return the sum, which 'transform' writes into the Output location.
                    return n + scalar;
                }
            );
            return result;
        }
        Matrix& operator+=(Number scalar) noexcept
        {
            std::ranges::transform(
                m_matrixArr | std::views::join,
                (m_matrixArr | std::views::join).begin(),
                [scalar](Number n)
                {
                    return n + scalar;
                }
            );
            return *this;
        }
    public:
        Matrix operator-(const Matrix& other) noexcept
        {
            // Left-Hand Side = LHS, Right-Hand Size = RHS
            Matrix result;
            auto self_flat = m_matrixArr | std::views::join;

            // Create a flattened view of the "other" object's (RHS) 2D array.
            auto other_flat = other.m_matrixArr | std::views::join;

            // Create a flattened view of the "result" matrix so we can write to it linearly.
            auto result_flat = result.m_matrixArr | std::views::join;
            // Perform the addition using the standard library algorithm.
            std::ranges::transform(
                self_flat,           // Input Range 1: The flattened Left-Hand Side matrix.
                other_flat,          // Input Range 2: The flattened Right-Hand Side matrix.
                result_flat.begin(), // Output Iterator: Where to start writing the results.
                std::minus{}          // The Operation: A standard functor that performs addition (x + y).
            );
            return result;
        }
        Matrix operator-=(const Matrix& other) noexcept
        {
            auto self_flat = m_matrixArr | std::views::join;
            auto other_flat = other.m_matrixArr | std::views::join;
            //auto result_flat = m_matrixArr | std::views::join;
            // Perform the addition using the standard library algorithm.
            std::ranges::transform(
                self_flat,           // Input Range 1: The flattened Left-Hand Side matrix.
                other_flat,          // Input Range 2: The flattened Right-Hand Side matrix.
                self_flat.begin(), // Output Iterator: Where to start writing the results.
                std::minus{}          // The Operation: A standard functor that performs addition (x + y).
            );
            return *this;
        }
        Matrix operator-(Number scalar) noexcept
        {
            Matrix result;
            std::ranges::transform(
                m_matrixArr | std::views::join,
                (result.m_matrixArr | std::views::join).begin(),
                [scalar](Number n)
                {
                    return n - scalar;
                }
            );
            return result;
        }
        Matrix& operator-=(Number scalar) noexcept
        {
            std::ranges::transform(
                m_matrixArr | std::views::join,
                (m_matrixArr | std::views::join).begin(),
                [scalar](Number n)
                {
                    return n - scalar;
                }
            );
            return *this;
        }
    public:
        Matrix operator*(Number scalar) noexcept
        {
            Matrix result;
            std::ranges::transform(
                m_matrixArr | std::views::join,
                (result.m_matrixArr | std::views::join).begin(),
                [scalar](Number n)
                {
                    return n * scalar;
                }
            );
            return result;
        }
        Matrix& operator*=(Number scalar) noexcept
        {
            std::ranges::transform(
                m_matrixArr | std::views::join,
                (m_matrixArr | std::views::join).begin(),
                [scalar](Number n)
                {
                    return n * scalar;
                }
            );
            return *this;
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
        std::array<std::array<Number, size>, size> m_matrixArr{T_zero_init<Number>()};
        static constexpr std::pair<uint8_t, uint8_t> MATRIX_SIZES_LIMITS{2,3};
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

}

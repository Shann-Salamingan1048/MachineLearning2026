#pragma once
#include "TemplateConstraint.h"
#include <print>

#include "Vectors.h"

namespace LinAlg
{
    template <typename T>
    concept VectorLike = requires(T t)
    {
        // REQUIREMENT 1: member variable 'data' must exist.
        // If T is 'int', 'int.data' is invalid -> Concept fails (returns false).
        // If T is 'Vector', 'Vector.data' is valid -> Concept passes (returns true).
        t.data;
    };
    // Uses CRTP: "Derived" lets the base class know who inherits it
    template<typename Derived, size_t size, typename Number>
    struct VectorBase
    {
        // data() -> it will find the member variable named "data" of the derived/child class
        // Helper to access the actual data in the Derived class
        //constexpr const auto& data(this const auto& self){return self.data;}
        //constexpr auto& data(this auto& self){return self.data;}
        // Addition
        constexpr auto operator+(this const auto& self, Number scalar) -> Derived
        {
            auto result = self;
            self += scalar;
            return result;
        }
        constexpr auto operator+=(this auto& self, Number scalar) -> Derived&
        {
            for (auto& n : self.data) n += scalar;
            return self;
        }
        constexpr auto operator+=(this auto& self, const VectorLike auto& other) -> Derived&
        {
            for (size_t i = 0; i < other.data.size(); ++i)
                self.data[i] = self.data[i] + other.data[i];
            return self;
        }
        friend constexpr auto operator+(const auto& self, const auto& other) -> Derived
        {
            auto result = self;
            result += other;
            return result;
        }
        friend constexpr auto operator+(const auto& self, Number scalar) -> Derived
        {
            auto result = self;
            result += scalar;
            return result;
        }
        // Subtraction
        constexpr auto operator-(this const auto& self, Number scalar) -> Derived
        {
            auto result = self;
            self -= scalar;
            return result;
        }
        constexpr auto operator-=(this auto& self, Number scalar) -> Derived&
        {
            for (auto& n : self.data) n -= scalar;
            return self;
        }
        constexpr auto operator-=(this auto& self, const VectorLike auto& other) -> Derived&
        {
            for (size_t i = 0; i < other.data.size(); ++i)
                self.data[i] = self.data[i] - other.data[i];
            return self;
        }
        friend constexpr auto operator-(const auto& self, const auto& other) -> Derived
        {
            auto result = self;
            result -= other;
            return result;
        }
        friend constexpr auto operator-(const auto& self, Number scalar) -> Derived
        {
            auto result = self;
            result -= scalar;
            return result;
        }
        // Multiplication
        constexpr auto operator*(this const auto& self, Number scalar) -> Derived
        {
            auto result = self;
            self *= scalar;
            return result;
        }
        constexpr auto operator*=(this auto& self, Number scalar) -> Derived&
        {
            for (auto& n : self.data) n *= scalar;
            return self;
        }
        constexpr auto operator*=(this auto& self, const VectorLike auto& other) -> Derived&
        {
            for (size_t i = 0; i < other.data.size(); ++i)
                self.data[i] = self.data[i] * other.data[i];
            return self;
        }
        friend constexpr auto operator*(const auto& self, const auto& other) -> Derived
        {
            auto result = self;
            result *= other;
            return result;
        }
        friend constexpr auto operator*(const auto& self, Number scalar) -> Derived
        {
            auto result = self;
            result *= scalar;
            return result;
        }
    };

    template<size_t size, Numeric Number>
    struct Vector : public VectorBase<Vector<size, Number>,size, Number>
    {
        std::array<Number, size> data{T_zero_init<Number>()};
        // 1. Mutable versions (Existing)
        // Accessors (instead of raw x, y, z members)
        /*
            The first version is called when you have a normal Vector v;.
            It returns a reference you can write to.
        */
        constexpr Number& x() requires (size >= 1) { return data[0]; }
        constexpr Number& y() requires (size >= 2) { return data[1]; }
        constexpr Number& z() requires (size >= 3) { return data[2]; }
        // 2. Const versions (NEW)
        // Allows: printVector(const Vector& v);
        constexpr const Number& x() const requires (size >= 1) { return data[0]; }
        constexpr const Number& y() const requires (size >= 2) { return data[1]; }
        constexpr const Number& z() const requires (size >= 3) { return data[2]; }
        /*
            The second version (marked const at the end) is called when you have
            a const Vector& v (like inside printVector). It returns a read-only reference.
        */
        // ONE constructor for everyone
        constexpr Vector(std::initializer_list<Number> init)
        {
            /* Generic logic that works for size 1, 3, or 100 */
            std::copy_n(init.begin(), std::min(init.size(), size), data.begin());
        }
        Vector() = default;
        friend void printVector(const Vector& v) noexcept
        {
            if constexpr  (size == 3)
            {
                std::println("Vector{}: x = {}, y = {}, z = {}\n", size, v.x(), v.y() , v.z());
            }
            else if constexpr(size == 2)
            {
                std::println("Vector{}: x = {}, y = {}\n", size, v.x(), v.y());
            }
            else if constexpr(size == 1)
            {
                std::println("Vector{}: x = {}\n", size, v.x());
            }
            else
            {
                std::println("Vector{}: {}", size, v.data);
            }
        }
        friend void roundOff(Vector& v,uint8_t decimalDigit) noexcept
        {
            auto TenPower = TenRaise(decimalDigit);
            if (!std::is_floating_point_v<Number>)
                return;
            std::ranges::transform(v.data,
                v.data.begin(),
                [TenPower](Number n)
                {
                    return std::round(n * TenPower) / TenPower;
                });
        }
    };

    using V1u8      =    Vector<1, uint8_t>;
    using V1u16     =    Vector<1, uint16_t>;
    using V1u32     =    Vector<1, uint32_t>;
    using V1u64     =    Vector<1, uint64_t>;
    using V1s       =    Vector<1, short>;
    using V1i       =    Vector<1, int>;
    using V1l       =    Vector<1, long>;
    using V1st      =    Vector<1, size_t>;
    using V1f       =    Vector<1, float>;
    using V1d       =    Vector<1, double>;

    using V2u8      =    Vector<2, uint8_t>;
    using V2u16     =    Vector<2, uint16_t>;
    using V2u32     =    Vector<2, uint32_t>;
    using V2u64     =    Vector<2, uint64_t>;
    using V2s       =    Vector<2, short>;
    using V2i       =    Vector<2, int>;
    using V2l       =    Vector<2, long>;
    using V2st      =    Vector<2, size_t>;
    using V2f       =    Vector<2, float>;
    using V2d       =    Vector<2, double>;

    using V3u8      =    Vector<3, uint8_t>;
    using V3u16     =    Vector<3, uint16_t>;
    using V3u32     =    Vector<3, uint32_t>;
    using V3u64     =    Vector<3, uint64_t>;
    using V3s       =    Vector<3, short>;
    using V3i       =    Vector<3, int>;
    using V3l       =    Vector<3, long>;
    using V3st      =    Vector<3, size_t>;
    using V3f       =    Vector<3, float>;
    using V3d       =    Vector<3, double>;

    using V4u8      =    Vector<4, uint8_t>;
    using V4u16     =    Vector<4, uint16_t>;
    using V4u32     =    Vector<4, uint32_t>;
    using V4u64     =    Vector<4, uint64_t>;
    using V4s       =    Vector<4, short>;
    using V4i       =    Vector<4, int>;
    using V4l       =    Vector<4, long>;
    using V4st      =    Vector<4, size_t>;
    using V4f       =    Vector<4, float>;
    using V4d       =    Vector<4, double>;

    using V10u8      =    Vector<10, uint8_t>;
    using V10u16     =    Vector<10, uint16_t>;
    using V10u32     =    Vector<10, uint32_t>;
    using V10u64     =    Vector<10, uint64_t>;
    using V10s       =    Vector<10, short>;
    using V10i       =    Vector<10, int>;
    using V10l       =    Vector<10, long>;
    using V10st      =    Vector<10, size_t>;
    using V10f       =    Vector<10, float>;
    using V10d       =    Vector<10, double>;
}

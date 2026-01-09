#pragma once
#include "TemplateConstraint.h"
#include <print>

#include "Vectors.h"

namespace LinAlg
{
    // Uses CRTP: "Derived" lets the base class know who inherits it
    template<typename Derived, size_t size, typename Number>
    struct VectorBase
    {
        // data() -> it will find the member variable named "data" of the derived/child class
        // Helper to access the actual data in the Derived class
        constexpr const auto& data() const { return static_cast<const Derived*>(this)->data; }
        constexpr auto& data() { return static_cast<Derived*>(this)->data; }

        Derived operator+(Number scalar)
        {
            Derived result;
            std::ranges::transform(this->data(),
                result->data().begin(),
                [scalar](Number n) {return n + scalar;});
            return result;
        }
        Derived& operator+=(Number scalar)
        {
            std::ranges::transform(this->data(),
                this->data().begin(),
                [scalar](Number n) {return n + scalar;});
            return *static_cast<Derived*>(this);
        }
        Derived& operator+=(const Derived& other)
        {
            std::ranges::transform(other.data, this->data(), this->data().begin(), std::plus{});
            return *static_cast<Derived*>(this);
        }
        friend Derived operator+(const Derived& other, const Derived& other2)
        {
            Derived result;
            std::ranges::transform(other.data, other2.data, result.data.begin(), std::plus{});
            return result;
        }
        Derived operator-(Number scalar)
        {
            Derived result;
            std::ranges::transform(this->data(),
                result->data().begin(),
                [scalar](Number n) {return n - scalar;});
            return result;
        }
        Derived& operator-=(Number scalar)
        {
            std::ranges::transform(this->data(),
                this->data().begin(),
                [scalar](Number n) {return n - scalar;});
            return *static_cast<Derived*>(this);
        }
        Derived& operator-=(const Derived& other)
        {
            std::ranges::transform(this->data(), other.data, this->data().begin(), std::minus{});
            return *static_cast<Derived*>(this);
        }
        friend Derived operator-(const Derived& other, const Derived& other2)
        {
            Derived result;
            std::ranges::transform(other.data, other2.data, result.data.begin(), std::minus<Number>{});
            return result;
        }
        Derived operator*(Number scalar)
        {
            Derived result;
            std::ranges::transform(this->data(),
                result->data().begin(),
                [scalar](Number n) {return n * scalar;});
            return result;
        }
        Derived& operator*=(Number scalar)
        {
            std::ranges::transform(this->data(),
                this->data().begin(),
                [scalar](Number n) {return n * scalar;});
            return *static_cast<Derived*>(this);
        }
        Derived& operator*=(const Derived& other)
        {
            //std::ranges::transform(other.data, this->data(), this->data().begin(), std::plus{});
            std::ranges::transform(other.data, this->data(), this->data().begin(), std::multiplies{});
            return *static_cast<Derived*>(this);
        }
        friend Derived operator*(const Derived& other, const Derived& other2)
        {
            Derived result;
            std::ranges::transform(other.data, other2.data, result.data.begin(), std::multiplies{});
            return result;
        }
    };

    template<size_t size, Numeric Number>
    struct Vector : public VectorBase<Vector<size, Number>, size, Number>
    {
        std::array<Number, size> data;
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
                std::println("Vector{}: x = {}, y = {}, z = {}", size, v.x(), v.y() , v.z());
            }
            else if constexpr(size == 2)
            {
                std::println("Vector{}: x = {}, y = {}", size, v.x(), v.y());
            }
            else if constexpr(size == 1)
            {
                std::println("Vector{}: x = {}", size, v.x());
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
}

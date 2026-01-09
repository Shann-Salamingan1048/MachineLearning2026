#pragma once
#include "TemplateConstraint.h"
#include <print>
namespace LinAlg
{
    template<Numeric Number>
    struct Vec1
    {
        Number x;
        Vec1() noexcept: x{T_zero_init<Number>()} {}
        explicit Vec1(Number x) noexcept: x{x} {}
        Vec1(const Vec1& other) noexcept = default;
        Vec1(Vec1&& other) noexcept = default;
        Vec1& operator=(const Vec1& other) noexcept = default;
        Vec1& operator=(Vec1&& other) noexcept = default;
        ~Vec1() = default;

        Vec1 operator+(Number scalar) const noexcept {return Vec1{x + scalar}; };
        Vec1 operator+(const Vec1& other) const noexcept {return Vec1{x + other.x}; };
        Vec1 operator-(Number scalar) const noexcept {return Vec1{x - scalar}; };
        Vec1 operator-(const Vec1& other) const noexcept {return Vec1{x - other.x}; };
        Vec1 operator*(Number scalar) const noexcept {return Vec1{x * scalar}; };
        Vec1 operator*(const Vec1& other) const noexcept {return Vec1{x * other.x}; };

        Vec1& operator+=(const Vec1& other) noexcept
        {
            x += other.x;
            return *this;
        };
        Vec1& operator-=(const Vec1& other) noexcept
        {
            x -= other.x;
            return *this;
        };
        Vec1& operator*=(const Vec1& other) noexcept
        {
            x *= other.x;
            return *this;
        };
        friend void printVec1(const Vec1& vec1) noexcept
        {
            std::println("Vec1: {}", vec1.x);
            std::println();
        }

    };
    using V1u8      =  Vec1<uint8_t>;
    using V1u16     =  Vec1<uint16_t>;
    using V1u32     =  Vec1<uint32_t>;
    using V1u64     =  Vec1<uint64_t>;
    using V1s       =  Vec1<short>;
    using V1i       =  Vec1<int>;
    using V1l       =  Vec1<long>;
    using V1st      =  Vec1<size_t>;
    using V1f       =  Vec1<float>;
    using V1d       =  Vec1<double>;

    template<Numeric Number>
    struct Vec2
    {
        Number x;
        Number y;
        Vec2() noexcept: x{T_zero_init<Number>()}, y{T_zero_init<Number>()} {}
        explicit Vec2(Number scalar) noexcept: x{scalar}, y{scalar} {}
        Vec2(const Vec2& other) noexcept = default;
        Vec2(Vec2&& other) noexcept = default;
        Vec2& operator=(const Vec2& other) noexcept = default;
        Vec2& operator=(Vec2&& other) noexcept = default;
        ~Vec2() = default;

        Vec2 operator+(Number scalar) const noexcept {return Vec2{x + scalar, y - scalar}; };
        Vec2 operator+(const Vec2& other) const noexcept {return Vec2{x + other.x, y - other.y}; };
        Vec2 operator-(Number scalar) const noexcept {return Vec2{x - scalar, y - scalar}; };
        Vec2 operator-(const Vec2& other) const noexcept {return Vec2{x - other.x, y - other.y}; };
        Vec2 operator*(Number scalar) const noexcept {return Vec2{x * scalar, y - scalar}; };
        Vec2 operator*(const Vec2& other) const noexcept {return Vec2{x * other.x, y - other.y}; };

        Vec2& operator+=(const Vec2& other) noexcept
        {
            x += other.x;
            y += other.y;
            return *this;
        };
        Vec2& operator-=(const Vec2& other) noexcept
        {
            x -= other.x;
            y -= other.y;
            return *this;
        };
        Vec2& operator*=(const Vec2& other) noexcept
        {
            x *= other.x;
            y *= other.y;
            return *this;
        };
        friend void printVec2(const Vec2& vec2) noexcept
        {
            std::println("Vec2: {}, {}", vec2.x, vec2.y);
            std::println();
        }
    };
    using V2u8      =  Vec2<uint8_t>;
    using V2u16     =  Vec2<uint16_t>;
    using V2u32     =  Vec2<uint32_t>;
    using V2u64     =  Vec2<uint64_t>;
    using V2s       =  Vec2<short>;
    using V2i       =  Vec2<int>;
    using V2l       =  Vec2<long>;
    using V2st      =  Vec2<size_t>;
    using V2f       =  Vec2<float>;
    using V2d       =  Vec2<double>;

    template<Numeric Number>
    struct Vec3
    {
        Number x;
        Number y;
        Number z;
        Vec3() noexcept: x{T_zero_init<Number>()}, y{T_zero_init<Number>()}, z{T_zero_init<Number>()} {}
        explicit Vec3(Number scalar) noexcept: x{scalar}, y{scalar}, z{scalar} {}
        Vec3(const Vec3& other) noexcept = default;
        Vec3(Vec3&& other) noexcept = default;
        Vec3& operator=(Vec3&& other) noexcept = default;
        Vec3& operator=(const Vec3& other) noexcept = default;
        ~Vec3() = default;

        Vec3 operator+(Number scalar) const noexcept {return Vec3{x + scalar, y - scalar, z - scalar}; };
        Vec3 operator+(const Vec3& other) const noexcept {return Vec3{x + other.x, y - other.y, z - other.z}; };
        Vec3 operator-(Number scalar) const noexcept {return Vec3{x - scalar, y - scalar, z - scalar}; };
        Vec3 operator-(const Vec3& other) const noexcept {return Vec3{x - other.x, y - other.y, z - other.z}; };
        Vec3 operator*(Number scalar) const noexcept {return Vec3{x * scalar, y - scalar, z - scalar}; };
        Vec3 operator*(const Vec3& other) const noexcept {return Vec3{x * other.x, y - other.y, z - other.z}; };

        Vec3& operator+=(const Vec3& other) noexcept
        {
            x += other.x;
            y += other.y;
            return *this;
        };
        Vec3& operator-=(const Vec3& other) noexcept
        {
            x -= other.x;
            y -= other.y;
            return *this;
        };
        Vec3& operator*=(const Vec3& other) noexcept
        {
            x *= other.x;
            y *= other.y;
            return *this;
        };
        friend void printVec3(const Vec3& vec3) noexcept
        {
            std::println("Vec3: {}, {}, {}", vec3.x, vec3.y, vec3.z);
            std::println();
        }
    };
    using V3u8      =  Vec3<uint8_t>;
    using V3u16     =  Vec3<uint16_t>;
    using V3u32     =  Vec3<uint32_t>;
    using V3u64     =  Vec3<uint64_t>;
    using V3s       =  Vec3<short>;
    using V3i       =  Vec3<int>;
    using V3l       =  Vec3<long>;
    using V3st      =  Vec3<size_t>;
    using V3f       =  Vec3<float>;
    using V3d       =  Vec3<double>;

}
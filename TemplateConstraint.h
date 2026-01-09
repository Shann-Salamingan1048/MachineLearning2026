#pragma once
#include <type_traits>
namespace LinAlg
{
    template<typename T>
    concept Numeric = std::is_arithmetic_v<T>; // only numeric data types

    template<Numeric Number>
    constexpr Number T_zero_init()
    {
        return{};
    }

    // Change return type to size_t to handle 10^3 (1000), 10^4 (10000), etc.
    constexpr size_t TenRaise(uint8_t Power) noexcept
    {
        size_t result = 1;
        for (uint8_t i = 0; i < Power; ++i)
        {
            result *= 10;
        }
        return result;
    }
}

#pragma once
#include <type_traits>
namespace LinAlg
{
    template<typename T>
    concept Numeric = std::is_arithmetic_v<T>; // only numeric data types

    template<Numeric Number>
    constexpr Number T_zero_init()
    {
        if constexpr (std::is_integral_v<Number>)
            return 0;
        else
            return 0.0;//Number(0.0);
    }
}

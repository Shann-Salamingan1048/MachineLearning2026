#pragma once

#include <print>
#include <array>


namespace Start
{
    struct Neuron
    {
        double weight;
        double bias;

        auto predict(double input) const noexcept -> double
        {
            return (weight * input) + bias;
        }
    };
    struct TrainingData
    {
        double input;
        double expectedOutput;
    };
    void Run();
}

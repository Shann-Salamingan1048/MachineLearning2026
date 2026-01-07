//
// Created by USER on 1/7/2026.
//

#include "Starting.h"
void Start::Run()
{
    static constexpr std::array<Start::TrainingData, 4> dataset
    { // its just (x * 2) + (5 * x)
        {
           {.input = 1.0, .expectedOutput = 7.0},
           {.input = 2.0, .expectedOutput = 14.0},
           {.input = 4.0, .expectedOutput = 28.0},
           {.input = 6.0, .expectedOutput = 42.0}
        }
    };

    Start::Neuron n;
    n.weight = 0.5;
    n.bias = 0.0;

    double learningRate = 0.05;
    uint16_t epochs = 500;
    std::println("Initial Guess: {}", n.predict(5.0));
    std::println("Training Daw......");

    for (uint16_t i = 0; i < epochs; ++i)
    {
        double totalError = 0.0;
        for (const auto& data : dataset)
        {
            double prediction = n.predict(data.input);
            double error = prediction - data.expectedOutput;

            n.weight -= learningRate * (error * data.input);
            n.bias -= learningRate * (error * 1.0);
            totalError += (error * error);
        }
    }
    std::println("Training Complete");
    std::println("Final Weight: {}", n.weight);
    std::println("Final Bias: {}", n.bias);

    double testValue = 10; // (10 * 2) + (5 * 10) = 20 + 50 = 70
    std::println("Result: {:.1f}", n.predict(testValue));
}
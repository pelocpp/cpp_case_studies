// =====================================================================================
// NeuronImpl.cpp
// =====================================================================================

#include "Common.h"
#include "Random.h"
#include "Neuron.h"

#include <cstddef>
#include <cmath>
#include <print>
#include <vector>

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

// c'tor(s)
Neuron::Neuron(std::size_t numOutputs, std::size_t index)
    : m_outputValue{}, m_index{ index }, m_gradient{}
{
    for (std::size_t i{}; i != numOutputs; ++i)
    {
        Connection conn{ .weight = random.nextRandomNumber(), .deltaWeight = 0.0 };
        //conn.weight = random.nextRandomNumber();
        //conn.deltaWeight = 0.0;
        m_outputWeights.push_back(conn);
    }
}

// public interface
void Neuron::setOutputValue(double val)
{
    m_outputValue = val; 
};

double Neuron::getOutputValue() const
{
    return m_outputValue;
};

double Neuron::getGradient() const
{
    return m_gradient;
};

void Neuron::calcOutputGradients(double targetVal)
{
    double delta{ targetVal - m_outputValue };
    m_gradient = delta * transferFunctionDerivative(m_outputValue);
}

void Neuron::calcHiddenGradients(const Layer& nextLayer)
{
    double dow{ sumDerivativeOfWeights(nextLayer) };
    m_gradient = dow * transferFunctionDerivative(m_outputValue);
}

void Neuron::updateInputWeights(Layer& prevLayer) const
{
    for (std::size_t n{}; n != prevLayer.size(); ++n)
    {
        Neuron& neuron{ prevLayer[n] };

        double oldDeltaWeight { neuron.m_outputWeights[m_index].deltaWeight };
        double newDeltaWeight{ eta * neuron.getOutputValue() * m_gradient + alpha * oldDeltaWeight };

        //std::println("oldDeltaWeight: {:08f}", oldDeltaWeight);
        //std::println("newDeltaWeight: {:08f}", newDeltaWeight);

        neuron.m_outputWeights[m_index].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[m_index].weight += newDeltaWeight;

      //  std::println("  Output Weight: {}", neuron.m_outputWeights[m_index].weight);
    }
}

double Neuron::transferFunction(double x)
{
    // tanh - output range [-1...1]
    return std::tanh(x);
}

double Neuron::transferFunctionDerivative(double x) {
    return 1.0 - x * x;
}

double Neuron::sumDerivativeOfWeights(const Layer& nextLayer) const
{
    double sum{};
    for (std::size_t n{}; n != nextLayer.size() - 1; ++n) {
        sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
    }
    return sum;
}

void Neuron::feedForward(const Layer& prevLayer)
{
    double sum{};

    // sum the previous layer's outputs (which are our inputs),
    // include the bias node from previous layer

    for (std::size_t n{}; n != prevLayer.size(); ++n) {
        sum += prevLayer[n].getOutputValue() * prevLayer[n].m_outputWeights[m_index].weight;
       // std::println("    SUM: {}", sum);
    }

    m_outputValue = Neuron::transferFunction(sum);

   // std::println("INDEX: {} -- m_outputValue: {}", m_index, m_outputValue);
}

// =====================================================================================
// End-of-File
// =====================================================================================

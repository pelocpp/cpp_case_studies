// =====================================================================================
// Neuron.h
// =====================================================================================

#pragma once

#include "Common.h"

#include <cstddef>
#include <vector>

class Neuron
{
private:
    double                     m_outputValue;
    std::vector<Connection>    m_outputWeights;
    std::size_t                m_index;
    double                     m_gradient;

public:
    // c'tor(s)
    Neuron                    (std::size_t numOutputs, std::size_t index);

    // getter / setter
    void   setOutputValue     (double value);
    double getOutputValue     () const;
    double getGradient        () const;

    // public interface
    void  feedForward         (const Layer& prevLayer);
    void  calcOutputGradients (double targetVal);
    void  calcHiddenGradients (const Layer& nextLayer);
    void  updateInputWeights  (Layer& prevLayer) const;

private:
    static double eta;       // Lernrate [0..1] 
    static double alpha;     // Momentum [0..n]

    double sumDerivativeOfWeights            (const Layer& nextLayer) const;
    static double transferFunction           (double x);
    static double transferFunctionDerivative (double x);
};

// =====================================================================================
// End-of-File
// =====================================================================================

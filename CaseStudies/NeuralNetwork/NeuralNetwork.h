// =====================================================================================
// NeuralNetwork.h
// =====================================================================================

#pragma once

#include "Common.h"

#include <cstddef>
#include <vector>

class NeuralNetwork
{
public:
    // c'tor(s)
    NeuralNetwork        ();

    // getter / setter
    void setTopology     (const Topology& topology);

    // public interface
    void feedForward     (const std::vector<double>& inputValues);
    void backProp        (const std::vector<double>& targetValues);
    void getResults      (std::vector<double>& resultValues) const;
    void print           () const;

private:
    std::vector<Layer>   m_layers;
    double               m_error;
};

// =====================================================================================
// End-of-File
// =====================================================================================

// =====================================================================================
// Common.h
// =====================================================================================

#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

// Hmm, hier oder wo anders ...
// Hmmm, std::pair oder so ...
struct Connection
{
    double weight;
    double deltaWeight;
};

using Topology = std::vector<std::size_t>;

class Neuron;
using Layer = std::vector<Neuron>;

// =====================================================================================
// End-of-File
// =====================================================================================

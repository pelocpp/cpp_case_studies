// =====================================================================================
// NeuralNetworkImpl.cpp
// =====================================================================================

#include "Common.h"
#include "NeuralNetwork.h"
#include "Neuron.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <print>
#include <stdexcept>
#include <vector>

// c'tor(s)
NeuralNetwork::NeuralNetwork()
    : m_error{}
{
}

// getter / setter
void NeuralNetwork::setTopology(const Topology& topology)
{
    std::size_t numLayers{ topology.size() };

    for (std::size_t layerNum{}; layerNum != numLayers; ++layerNum) {

        m_layers.push_back(Layer());

        // the hidden layers does have the number of outputs specified in the topology object,
        // the output layer does not have any outputs.
        std::size_t numOutputs{ layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1] };

        // we have made a new layer, now fill it with neurons
        for (std::size_t neuronNum{}; neuronNum != topology[layerNum]; ++neuronNum) {

            Neuron neuron{ numOutputs, neuronNum };
            m_layers.back().push_back(neuron);
        }

        // create finally a bias neuron
        Neuron bias{ numOutputs, topology[layerNum] };

        // force the bias node's output value to be initially 1.0
        bias.setOutputValue(1.0);

        // add bias neuron to the layer, it's the last neuron created in the current layer
        m_layers.back().push_back(bias);
    }
}


// public interface
void NeuralNetwork::feedForward(const std::vector<double>& inputValues)
{
    if (inputValues.size() != m_layers[0].size() - 1) {
        throw std::invalid_argument("Wrong number of inputs");
    }

    for (std::size_t i{}; i != inputValues.size(); ++i) {
        m_layers[0][i].setOutputValue(inputValues[i]);
    }
        
    for (std::size_t layerNum{ 1 }; layerNum != m_layers.size(); ++layerNum) {

        const std::vector<Neuron>& prevLayer{ m_layers[layerNum - 1] };
        for (std::size_t n{}; n != m_layers[layerNum].size() - 1; ++n) {
            m_layers[layerNum][n].feedForward(prevLayer);
        }
    }
}

void NeuralNetwork::backProp(const std::vector<double>& targetValues)
{
    std::vector<Neuron>& outputLayer{ m_layers.back() };

    // calculate the RMSE (Root Mean Square Error):
    // a metric used in machine learning to evaluate the quality of predictions,
    // calculated as the square root of the average of squared differences between predicted and actual values.

    m_error = 0.0;

    for (std::size_t n{}; n != outputLayer.size() - 1; ++n) {

        double delta{ targetValues[n] - outputLayer[n].getOutputValue() };
        m_error += delta * delta;
    }

    m_error /= outputLayer.size() - 1;
    m_error = std::sqrt(m_error);

    // calculate output layer gradients
    for (std::size_t n{}; n != outputLayer.size() - 1; ++n) {
        outputLayer[n].calcOutputGradients(targetValues[n]);
    }

    // calculate gradients on hidden layers
    for (std::size_t layerNum{ m_layers.size() - 2 }; layerNum != 0; --layerNum) {

        std::vector<Neuron>& hiddenLayer{ m_layers[layerNum] };
        std::vector<Neuron>& nextLayer{ m_layers[layerNum + 1] };

        for (std::size_t n{}; n != hiddenLayer.size(); ++n) {
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    // for all layers from outputs to first hidden layer, update connection weights
    for (std::size_t layerNum{ m_layers.size() - 1 }; layerNum != 0; --layerNum) {

        std::vector<Neuron>& layer{ m_layers[layerNum] };
        std::vector<Neuron>& prevLayer{ m_layers[layerNum - 1] };

        for (std::size_t n{}; n != layer.size() - 1; ++n) {
            layer[n].updateInputWeights(prevLayer);
        }
    }
}

void NeuralNetwork::getResults(std::vector<double>& resultValues) const
{
    resultValues.clear();

    for (std::size_t n{}; n != m_layers.back().size() - 1; ++n) {
        resultValues.push_back(m_layers.back()[n].getOutputValue());
    }
}

void NeuralNetwork::print() const
{
    std::size_t maxLayerLength{};

    auto it = std::max_element(
        m_layers.begin(),
        m_layers.end(),
        [](const auto& layer1, const auto& layer2) {
            return layer1.size() < layer2.size();
        }
    );

    if (it != m_layers.end()) {
        maxLayerLength = it->size();
    }

    std::println("NeuralNetwork:");
    for (std::size_t row{}; row != maxLayerLength; ++row) {

        for (std::size_t col{}; col != m_layers.size(); ++col) {

            if (row < m_layers[col].size()) {
                const Neuron& neuron{ m_layers[col][row] };
                std::print("[{}][{}]: Value: {:3}  ", row, col, neuron.getOutputValue());
            }
            else {
                std::print("[{}][{}]: {:15}", row, col, "");
            }
        }
        std::println();
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================

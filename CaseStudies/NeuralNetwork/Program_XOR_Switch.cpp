// =====================================================================================
// Program_XOR_Switch.cpp
// =====================================================================================

#include "../ScopedTimer.h"

#include "Common.h"
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "TrainingAndTestData_XOR_Switch.h"

#include <algorithm>
#include <cstddef>
#include <print>
#include <stdexcept>
#include <vector>

static TrainingAndTestData_XOR_Switch g_dataset{};    // want neural network data to be global
static NeuralNetwork                  g_net{};        // want neural network to be global

static void main_neural_network_xor_simulation_01_prepare_data()
{
    std::println("Start Loading Data ...");

    ScopedTimer guard{};

    g_dataset.setFilenames(
        "XOR_Training_Data.txt",
        "XOR_Test_Data.txt"
    );

    g_dataset.loadData();

    std::println("Loading Data Done.");
}

static void main_neural_network_xor_simulation_02_training()
{
    std::println("Starting Training ...");

    ScopedTimer guard{};

    const Topology& topology = g_dataset.getTopology();

    std::size_t outputLayerSize{ topology.back() };

    g_net.setTopology(topology);

    std::vector<double> resultValues{};

    std::size_t trainingPasses{};

    while (!g_dataset.isEndOfTrainingData())
    {
        ++trainingPasses;

        if (trainingPasses % 1000 == 0) {
            std::println("Training Passes {}.", trainingPasses);
        }

        const std::vector<double>& inputValues = g_dataset.nextTrainingInput();

        g_net.feedForward(inputValues);

        // collect the net's actual output results
        g_net.getResults(resultValues);

        // train the net what the outputs should have been
        const std::vector<double> targetValues = g_dataset.nextTrainingTargetOutput();

        if (targetValues.size() != outputLayerSize) {
            throw std::invalid_argument("Wrong number of target values!");
        }

        g_net.backProp(targetValues);

        g_dataset.advanceTraining();
    }

    std::println("Training Done.");
}

static void main_neural_network_xor_simulation_03_test()
{
    std::println("Starting Test ...");

    ScopedTimer guard{};

    std::vector<double> resultValues{};

    std::size_t testPasses{};
    std::size_t correct{};

    while (!g_dataset.isEndOfTestData())
    {
        ++testPasses;

        if (testPasses % 1000 == 0) {
            std::println("Test Passes {}.", testPasses);
        }

        const std::vector<double>& inputValues = g_dataset.nextTestInput();

        g_net.feedForward(inputValues);

        g_net.getResults(resultValues);

        double predictedValue{ resultValues[0] };
        const std::vector<double>& targetValues{ g_dataset.nextTestTargetOutput() };
        double resultValue{ targetValues[0] };
        double delta{ std::abs(predictedValue - resultValue) };

        if (delta < 0.1) {
            correct++;
        }

        g_dataset.advanceTest();
    }

    std::println("Correct Results: {}", correct);
    std::println("Test Passes:     {}", testPasses);

    double testAccuracy = 100.0 * correct / testPasses;
    std::println("Test accuracy: {}%", testAccuracy);

    std::println("Test Done.");
}

void main_neural_network_xor_switch_simulation()
{
    main_neural_network_xor_simulation_01_prepare_data();
    main_neural_network_xor_simulation_02_training();
    main_neural_network_xor_simulation_03_test();
}

// =====================================================================================
// End-of-File
// =====================================================================================

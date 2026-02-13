// =====================================================================================
// Program_MNIST.cpp
// =====================================================================================

#include "../ScopedTimer.h"

#include "Common.h"
#include "NeuralNetwork.h"
#include "Neuron.h"
#include "TrainingAndTestData_MNIST.h"

#include <algorithm>
#include <cstddef>
#include <print>
#include <stdexcept>
#include <vector>

static TrainingAndTestData_MNIST g_dataset{};  // want neural network data to be global
static NeuralNetwork             g_net{};      // want neural network to be global

static void showVectorValues(const std::string& label, const std::vector<double>& vec)
{
    std::print("{} ", label);
    for (std::size_t i{}; i != vec.size(); ++i) {
        std::print("{:5f} ", vec[i]);
    }
    std::println();
}

static void main_neural_network_mnist_simulation_01_prepare_data()
{
    std::println("Start Loading Data ...");

    ScopedTimer guard{};

    // Overview:
    // train-images-idx3-ubyte:  60.000 images for training.
    // train-labels-idx1-ubyte:  60.000 correct digits according to the training images.
    // t10k-images-idx3-ubyte:   10.000 images for testing.
    // t10k-labels-idx1-ubyte:   10.000 correct digits according to the testing images.

    g_dataset.setFilenames(
        "..\\Resources\\train-images-idx3-ubyte",
        "..\\Resources\\train-labels-idx1-ubyte",
        "..\\Resources\\t10k-images-idx3-ubyte",
        "..\\Resources\\t10k-labels-idx1-ubyte"
    );

    g_dataset.loadData();

    std::println("Loading Data Done.");
}

static void main_neural_network_mnist_simulation_02_training()
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

         // assert(targetValues.size() == topology.back());
        if (targetValues.size() != outputLayerSize) {
            throw std::invalid_argument("Wrong number of target values!");
        }

        g_net.backProp(targetValues);

        g_dataset.advanceTraining();
    }

    std::println("Training Done.");
}

static void main_neural_network_mnist_simulation_03_test()
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

        std::size_t predicted = std::distance(
            resultValues.begin(),
            std::max_element(resultValues.begin(), resultValues.end())
        );

        const std::vector<double>& targetValues = g_dataset.nextTestTargetOutput();

        std::size_t actual = std::distance(
            targetValues.begin(),
            std::max_element(
                targetValues.begin(),
                targetValues.end()
            )
        );

        if (predicted == actual) {
            correct++;
        }

        g_dataset.advanceTest();
    }

    std::println("Correct Results: {}", correct);
    std::println("Test Passes:     {}", testPasses);

    double testAccuracy = 100.0 * correct / testPasses;
    std::println("Test accuracy: {}", testAccuracy);

    std::println("Test Done.");
}

void main_neural_network_mnist_simulation()
{
    main_neural_network_mnist_simulation_01_prepare_data();
    main_neural_network_mnist_simulation_02_training();
    main_neural_network_mnist_simulation_03_test();
}

// =====================================================================================
// End-of-File
// =====================================================================================

// =====================================================================================
// Program.cpp
// =====================================================================================

#include "Common.h"
#include "Random.h"
#include "Neuron.h"
#include "NeuralNetwork.h"

#include <print>

extern void main_neural_network_mnist_simulation();
extern void main_neural_network_xor_switch_simulation();

RandomWeights random{ 123, true };

static void main_neural_net_01()
{
    for (std::size_t i{}; i != 5; ++i) {

        auto number{ random.nextRandomNumber() };
        std::println("{}: {}", i, number);
    }
    std::cout << std::endl;
    std::println();
}

static void main_neural_net_02()
{
    Topology topology{ 3, 4, 1 };
    NeuralNetwork net{};
    net.setTopology(topology);
    net.print();
}

int main()
{
    //main_neural_net_01();
    //main_neural_net_02();

    main_neural_network_mnist_simulation();
    //main_neural_network_xor_switch_simulation();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================

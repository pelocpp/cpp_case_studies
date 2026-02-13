//neural-net-tutorial.cpp

#include "Random.h"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <vector>

namespace Tutorial_David_Miller_Original {

    class TrainingData
    {
    public:
        TrainingData(const std::string filename);
        bool isEof(void) { return m_trainingDataFile.eof(); }
        void getTopology(std::vector<unsigned>& topology);

        // Returns the number of input values read from the file:
        unsigned getNextInputs(std::vector<double>& inputVals);
        unsigned getTargetOutputs(std::vector<double>& targetOutputVals);

    private:
        std::ifstream m_trainingDataFile;
    };

    void TrainingData::getTopology(std::vector<unsigned>& topology)
    {
        std::string line;
        std::string label;

        getline(m_trainingDataFile, line);
        std::stringstream ss(line);
        ss >> label;
        if (this->isEof() || label.compare("topology:") != 0) {
            abort();
        }

        while (!ss.eof()) {
            unsigned n;
            ss >> n;
            topology.push_back(n);
        }

        return;
    }

    TrainingData::TrainingData(const std::string filename)
    {
        m_trainingDataFile.open(filename.c_str());
    }

    unsigned int TrainingData::getNextInputs(std::vector<double>& inputVals)
    {
        inputVals.clear();

        std::string line;
        getline(m_trainingDataFile, line);
        std::stringstream ss(line);

        std::string label;
        ss >> label;
        if (label.compare("in:") == 0) {
            double oneValue;
            while (ss >> oneValue) {
                inputVals.push_back(oneValue);
            }
        }

        return (unsigned int) inputVals.size();
    }

    unsigned TrainingData::getTargetOutputs(std::vector<double>& targetOutputVals)
    {
        targetOutputVals.clear();

        std::string line;
        getline(m_trainingDataFile, line);
        std::stringstream ss(line);

        std::string label;
        ss >> label;
        if (label.compare("out:") == 0) {
            double oneValue;
            while (ss >> oneValue) {
                targetOutputVals.push_back(oneValue);
            }
        }

        return (unsigned int) targetOutputVals.size();
    }

    struct Connection
    {
        double weight;
        double deltaWeight;
    };

    class Neuron;

    typedef std::vector<Neuron> Layer;

    // **************** class Neuron ****************

    class Neuron
    {
    public:
        Neuron(unsigned numOutputs, unsigned myIndex);
        void setOutputVal(double val) { m_outputVal = val; };
        double getOutputVal(void) const {
            return m_outputVal; 
        };
        double getGradient() const {
            return m_gradient;
        };;

        void feedForward(const Layer& prevLayer);
        void calcOutputGradients(double targetVal);
        void calcHiddenGradients(const Layer& nextLayer);
        void updateInputWeights(Layer& prevLayer) const;

    private:
        static double eta; // [0..1] overall net training rate
        static double alpha; // [0..n] multiplier of last weight change (momentum)
        static double transferFunction(double x);
        static double transferFunctionDerivative(double x);
        
        // static double randomWeight(void) { return rand() / double(RAND_MAX); }
        static double randomWeight(void) { return random.nextRandomNumber(); }

        double sumDOW(const Layer& nextLayer) const;
        double m_outputVal;
        std::vector<Connection> m_outputWeights;
        unsigned m_myIndex;
        double m_gradient;
    };

    double Neuron::eta = 0.15; // overall net learning rate
    double Neuron::alpha = 0.5; // momentum, multiplier of last deltaWeight

    Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
    {
        for (unsigned c = 0; c < numOutputs; ++c) {
            m_outputWeights.push_back(Connection());
            m_outputWeights.back().weight = randomWeight();
        }

        m_myIndex = myIndex;
    }

    double Neuron::transferFunction(double x)
    {
        // tanh - output range [-1...1]
        return tanh(x);
    }

    double Neuron::transferFunctionDerivative(double x)
    {
        // tanh derivative
        return 1.0 - x * x;
    }

    void Neuron::feedForward(const Layer& prevLayer)
    {
        double sum = 0.0;

        // sum the previous layer's outputs (which are our inputs)
        // include the bias node from previous layer

        for (unsigned n = 0; n < prevLayer.size(); ++n) {
            sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].weight;
           // std::println("    sum: {}", sum);
        }

        m_outputVal = Neuron::transferFunction(sum);

     //   std::println("INDEX: {} -- m_outputValue: {}", m_myIndex, m_outputVal);
    }

    void Neuron::calcOutputGradients(double targetVal)
    {
        double delta = targetVal - m_outputVal;
        m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
    }

    void Neuron::calcHiddenGradients(const Layer& nextLayer)
    {
        double dow = sumDOW(nextLayer);
        m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
    }

    void Neuron::updateInputWeights(Layer& prevLayer) const
    {
        // the weights to be updated are in the Connection container
        // in the neurons in the preceeding layer

        for (unsigned n = 0; n < prevLayer.size(); ++n) {

            Neuron& neuron = prevLayer[n];
            
            double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

            double newDeltaWeight =
                // individual input, magnified by the gradient and train rate:
                eta
                * neuron.getOutputVal()
                * m_gradient
                // also add momentum = a fraction of the previous delta weight
                + alpha
                * oldDeltaWeight;

            //std::println("oldDeltaWeight: {:08f}", oldDeltaWeight);
            //std::println("newDeltaWeight: {:08f}", newDeltaWeight);

            neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
            neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;

          //  std::println("  Output Weight: {}", neuron.m_outputWeights[m_myIndex].weight);
        }
    }

    double Neuron::sumDOW(const Layer& nextLayer) const
    {
        double sum = 0.0;

        // sum our contributions of the errors at the nodes we feed

        for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
            sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
        }

        return sum;
    }

    // **************** class Net ****************

    class Net
    {
    public:
        Net(const std::vector<unsigned>& topology);
        void feedForward(const std::vector<double>& inputVals);
        void backProp(const std::vector<double>& targetVals);
        void getResults(std::vector<double>& resultVals) const;
        double getRecentAverageError(void) const { return m_recentAverageError; }

    private:
        std::vector<Layer> m_layers; //m_layers[layerNum][neuronNum]
        double m_error;
        double m_recentAverageError;
        double m_recentAverageSmoothingFactor;
    };

    Net::Net(const std::vector<unsigned>& topology)
    {
        unsigned numLayers = (unsigned int)topology.size();

        for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
        
            m_layers.push_back(Layer());
            unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

            // we have made a new layer, now fill it with neurons and 
            // add a bias neuron to the layer:
            for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
                m_layers.back().push_back(Neuron(numOutputs, neuronNum));
                std::cout << "Made a Neuron!" << std::endl;
            }

            // force the bias node's output value to 1.0. It's the last neuron created above
            m_layers.back().back().setOutputVal(1.0);
        }
    }

    void Net::feedForward(const std::vector<double>& inputVals)
    {
        assert(inputVals.size() == m_layers[0].size() - 1);

        // assign (latch) the input values into the input neurons
        for (unsigned i = 0; i < inputVals.size(); ++i) {
            m_layers[0][i].setOutputVal(inputVals[i]);
        }

        // forward propagate
        for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
            Layer& prevLayer = m_layers[layerNum - 1];
            for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) {
                m_layers[layerNum][n].feedForward(prevLayer);
            }
        }
    }

    void Net::backProp(const std::vector<double>& targetVals)
    {
        // calc overall net error (rms of output neuron errors)

        Layer& outputLayer = m_layers.back();
        m_error = 0.0;

        for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
            double delta = targetVals[n] - outputLayer[n].getOutputVal();
            m_error += delta * delta;
        }

  //      std::println("m_error 01: {}", m_error);

        m_error /= outputLayer.size() - 1;
        m_error = sqrt(m_error);  // RMS

  //      std::println("m_error 02: {}", m_error);

        // implement a recent avg measurement
        m_recentAverageError =
            (m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
            / (m_recentAverageSmoothingFactor + 1.0);

   //     std::println("m_recentAverageError 03: {}", m_recentAverageError);


        // calc output layer gradients

        for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
            outputLayer[n].calcOutputGradients(targetVals[n]);

         //   std::println("Output Gradient: {}", outputLayer[n].getGradient());
        }

        // calc gradients on hidden layers

        for (unsigned layerNum = (unsigned int) m_layers.size() - 2; layerNum > 0; --layerNum) {

            Layer& hiddenLayer = m_layers[layerNum];
            Layer& nextLayer = m_layers[layerNum + 1];

            for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
                hiddenLayer[n].calcHiddenGradients(nextLayer);

               // std::println("Hidden Gradient: {}", hiddenLayer[n].getGradient());
            }
        }

        // for all layers from outputs to first hidden layer,
        // update connection weights

        for (unsigned layerNum = (unsigned int) m_layers.size() - 1; layerNum > 0; --layerNum) {

            Layer& layer = m_layers[layerNum];
            Layer& prevLayer = m_layers[layerNum - 1];

            for (unsigned n = 0; n < layer.size() - 1; ++n) {
                layer[n].updateInputWeights(prevLayer);
            }
        }
    }

    void Net::getResults(std::vector<double>& resultVals) const
    {
        resultVals.clear();

        for (unsigned n = 0; n < m_layers.back().size() - 1; ++n)
        {
            resultVals.push_back(m_layers.back()[n].getOutputVal());
        }
    }

    static void showVectorVals(std::string label, std::vector<double>& vec)
    {
        std::print("{} ", label);
        for (std::size_t i{}; i != vec.size(); ++i) {
            std::print("{:5f} ", vec[i]);
        }
        std::println();
    }

    static void create_neural_net_training_samples()
    {
        // random traning sets for XOR -- two inputs and one output

        std::cout << "topology: 2 4 1" << std::endl;
        for (int i = 2000; i >= 0; --i) {
            int n1 = (int)(2.0 * rand() / double(RAND_MAX));
            int n2 = (int)(2.0 * rand() / double(RAND_MAX));
            int t = n1 ^ n2; // should be 0 or 1
            std::cout << "in: " << n1 << ".0 " << n2 << ".0 " << std::endl;
            std::cout << "out: " << t << ".0" << std::endl;
        }
    }

    static void main_neural_net_simulation()
    {
        TrainingData trainData("trainingData.txt");   // Topology: 2 4 1

        // e.g., { 3, 2, 1 } 
        std::vector<unsigned> topology;
        trainData.getTopology(topology);

        Net myNet(topology);

        std::vector<double> inputVals, targetVals, resultVals;
        int trainingPass = 0;

        //while (trainingPass != 1)
        //{

        while (!trainData.isEof())
        {
            // Get new input data and feed it forward:
            if (trainData.getNextInputs(inputVals) != topology[0]) {
                break;
            }

            ++trainingPass;
            std::cout << std::endl << "Pass " << trainingPass;

            showVectorVals(": Inputs:", inputVals);
            myNet.feedForward(inputVals);

            // Collect the net's actual output results:
            myNet.getResults(resultVals);
            showVectorVals("Outputs:", resultVals);

            // Train the net what the outputs should have been:
            trainData.getTargetOutputs(targetVals);
            showVectorVals("Targets:", targetVals);
            assert(targetVals.size() == topology.back());

            myNet.backProp(targetVals);

            // Report how well the training is working, average over recent samples:
            //std::cout << "Net recent average error: "
            //    << myNet.getRecentAverageError() << std::endl;
            std::println("Neural Netword recent average error: {:6f}", myNet.getRecentAverageError());
        }

        std::cout << std::endl << "Done" << std::endl;
    }
}

static void main_neural_net()
{
    //Tutorial_David_Miller_Original::create_neural_net_training_samples();
    Tutorial_David_Miller_Original::main_neural_net_simulation();
}

#include "..\ScopedTimer.h"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <print>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace Tutorial_David_Miller_Using_MNIST_and_ChatGPT {

    // INCLUDE ANTEIL

    // =======================
    // Connection
    // =======================
    struct Connection {
        double weight;
        double deltaWeight;
    };

    // =======================
    // Neuron
    // =======================
    class Neuron {
    public:
        Neuron(unsigned numOutputs, unsigned myIndex);
        void setOutputVal(double val) { m_outputVal = val; }
        double getOutputVal() const { return m_outputVal; }

        void feedForward(const vector<Neuron>& prevLayer);
        void calcOutputGradients(double targetVal);
        void calcHiddenGradients(const vector<Neuron>& nextLayer);
        void updateInputWeights(vector<Neuron>& prevLayer);

    private:
        static double eta;    // Lernrate
        static double alpha;  // Momentum

        static double transferFunction(double x);
        static double transferFunctionDerivative(double x);
        static double randomWeight() { return rand() / double(RAND_MAX); }

        double sumDOW(const vector<Neuron>& nextLayer) const;

        double m_outputVal;
        vector<Connection> m_outputWeights;
        unsigned m_myIndex;
        double m_gradient;
    };

    // =======================
    // Net
    // =======================

    class Net {
    public:
        Net(const vector<unsigned>& topology);

        void feedForward(const vector<double>& inputVals);
        void backProp(const vector<double>& targetVals);
        void getResults(vector<double>& resultVals) const;

    private:
        vector<vector<Neuron>> m_layers;
        double m_error;
    };

    // =======================================================
    // Implementation

    // Initialisierung statischer Member
    double Neuron::eta = 0.05;
    double Neuron::alpha = 0.5;

    // =======================
    // Neuron
    // =======================
    Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
        : m_myIndex(myIndex) {
        for (unsigned c = 0; c < numOutputs; ++c) {
            m_outputWeights.push_back(Connection());
            m_outputWeights.back().weight = randomWeight();
            m_outputWeights.back().deltaWeight = 0.0;
        }
    }

    double Neuron::transferFunction(double x) {
        return tanh(x);
    }

    double Neuron::transferFunctionDerivative(double x) {
        return 1.0 - x * x;
    }

    void Neuron::feedForward(const vector<Neuron>& prevLayer) {
        double sum = 0.0;

        for (unsigned n = 0; n < prevLayer.size(); ++n) {
            sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].weight;
        }

        m_outputVal = transferFunction(sum);
    }

    void Neuron::calcOutputGradients(double targetVal) {
        double delta = targetVal - m_outputVal;
        m_gradient = delta * transferFunctionDerivative(m_outputVal);
    }

    void Neuron::calcHiddenGradients(const vector<Neuron>& nextLayer) {
        double dow = sumDOW(nextLayer);
        m_gradient = dow * transferFunctionDerivative(m_outputVal);
    }

    void Neuron::updateInputWeights(vector<Neuron>& prevLayer) {
        for (unsigned n = 0; n < prevLayer.size(); ++n) {
            Neuron& neuron = prevLayer[n];
            double oldDeltaWeight =
                neuron.m_outputWeights[m_myIndex].deltaWeight;

            double newDeltaWeight =
                eta * neuron.getOutputVal() * m_gradient
                + alpha * oldDeltaWeight;

            neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
            neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
        }
    }

    double Neuron::sumDOW(const vector<Neuron>& nextLayer) const {
        double sum = 0.0;

        for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
            sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
        }

        return sum;
    }

    // =======================
    // Net
    // =======================

    Net::Net(const vector<unsigned>& topology) : m_error{} {

        for (unsigned layerNum = 0; layerNum < topology.size(); ++layerNum) {
        
            m_layers.push_back(vector<Neuron>());
            
            unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

            for (unsigned neuronNum = 0; neuronNum <= topology[layerNum];  ++neuronNum)
            {
                m_layers.back().push_back(Neuron(numOutputs, neuronNum));
            }

            // Bias-Neuron
            m_layers.back().back().setOutputVal(1.0);
        }
    }

    void Net::feedForward(const vector<double>& inputVals) {

        assert(inputVals.size() == m_layers[0].size() - 1);

        for (unsigned i = 0; i < inputVals.size(); ++i)
            m_layers[0][i].setOutputVal(inputVals[i]);

        for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
            const vector<Neuron>& prevLayer = m_layers[layerNum - 1];
            for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
                m_layers[layerNum][n].feedForward(prevLayer);
        }
    }

    void Net::backProp(const vector<double>& targetVals) {
        vector<Neuron>& outputLayer = m_layers.back();
        m_error = 0.0;

        for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
            double delta = targetVals[n] - outputLayer[n].getOutputVal();
            m_error += delta * delta;
        }

        m_error /= outputLayer.size() - 1;
        m_error = sqrt(m_error);

        for (unsigned n = 0; n < outputLayer.size() - 1; ++n)
            outputLayer[n].calcOutputGradients(targetVals[n]);

        for (unsigned layerNum = (unsigned int)m_layers.size() - 2; layerNum > 0; --layerNum) {

            vector<Neuron>& hiddenLayer = m_layers[layerNum];
            vector<Neuron>& nextLayer = m_layers[layerNum + 1];

            for (unsigned n = 0; n < hiddenLayer.size(); ++n)
                hiddenLayer[n].calcHiddenGradients(nextLayer);
        }

        for (unsigned layerNum = (unsigned int)m_layers.size() - 1; layerNum > 0; --layerNum) {

            vector<Neuron>& layer = m_layers[layerNum];
            vector<Neuron>& prevLayer = m_layers[layerNum - 1];

            for (unsigned n = 0; n < layer.size() - 1; ++n)
                layer[n].updateInputWeights(prevLayer);
        }
    }

    void Net::getResults(vector<double>& resultVals) const {
        resultVals.clear();

        for (unsigned n = 0; n < m_layers.back().size() - 1; ++n)
            resultVals.push_back(m_layers.back()[n].getOutputVal());
    }
}

// ===============================================================

namespace Tutorial_David_Miller_Using_MNIST_and_ChatGPT {

    struct MNISTDataset {
        std::vector<std::vector<double>> images;
        std::vector<std::vector<double>> labels;
    };

    MNISTDataset loadMNIST(
        const std::string& imageFile,
        const std::string& labelFile,
        int limit = -1
    );


    static int readInt(std::ifstream& file) {
        unsigned char bytes[4];
        file.read((char*)bytes, 4);
        return (bytes[0] << 24) | (bytes[1] << 16)
            | (bytes[2] << 8) | bytes[3];
    }

    MNISTDataset loadMNIST(
        const std::string& imageFile,
        const std::string& labelFile,
        int limit
    ) {
        std::ifstream images(imageFile, std::ios::binary);
        std::ifstream labels(labelFile, std::ios::binary);

        if (!images || !labels)
            throw std::runtime_error("MNIST-Dateien konnten nicht geöffnet werden");

    //    int magicImages = readInt(images);
        int numImages = readInt(images);
        int rows = readInt(images);
        int cols = readInt(images);

      //  int magicLabels = readInt(labels);
        int numLabels = readInt(labels);

        if (numImages != numLabels)
            throw std::runtime_error("Bild-/Label-Anzahl stimmt nicht überein");

        if (limit > 0 && limit < numImages)
            numImages = limit;

        MNISTDataset dataset;

        for (int i = 0; i < numImages; ++i) {
            // --- Bild ---
            std::vector<double> image(rows * cols);
            for (int p = 0; p < rows * cols; ++p) {
                unsigned char pixel{};
                images.read((char*)&pixel, 1);
                // image[p] = pixel / 255.0;  // Normalisierung

                // Added: PeLo: =================================
                // BESSER wegen tanh: Eine Normierung auf [-1.0, 1.0]
                 image[p] = (pixel / 255.0) * 2.0 - 1.0;
            }

            dataset.images.push_back(image);

            // --- Label ---
            unsigned char label;
            labels.read((char*)&label, 1);

            // One-Hot-Encoding: 0.0 / 1.0
            //std::vector<double> target(10, 0.0);
            //target[label] = 1.0; 
            //dataset.labels.push_back(target);

            // Added: PeLo: =================================
            // BESSER wegen tanh: Eine Normierung auf [-1.0, 1.0]
            std::vector<double> target(10, -1.0);
            target[label] = 1.0;
            dataset.labels.push_back(target);
        }

        return dataset;
    }
}

static void main_neural_net_mnist_and_chatgpt()
{
    using namespace Tutorial_David_Miller_Using_MNIST_and_ChatGPT;

    ScopedTimer watch{};

    vector<unsigned> topology = { 784, 100, 10 };

    Net myNet(topology);

    auto trainData = loadMNIST(
        "../Resources/train-images-idx3-ubyte",
        "../Resources/train-labels-idx1-ubyte",
        60000
    );

    // --- Train ---
   for (size_t i = 0; i < trainData.images.size(); ++i) {
   // for (size_t i = 0; i < 1000; ++i) {  // Ändern // EINE ZEILE OBEN // NUR ZUM TESTEN !!!
        myNet.feedForward(trainData.images[i]);
        myNet.backProp(trainData.labels[i]);

        if (i % 1000 == 0) {
            std::cout << "Trainingsbeispiel: " << i << std::endl;
        }
    }

    // --- Test ---
    auto testData = loadMNIST(
        "../Resources/t10k-images-idx3-ubyte",
        "../Resources/t10k-labels-idx1-ubyte"
    );

    int correct = 0;

    for (size_t i = 0; i < testData.images.size(); ++i)
    {
        myNet.feedForward(testData.images[i]);

        vector<double> result;
        myNet.getResults(result);

        if (i % 1000 == 0) {
            std::cout << "Testbeispiel: " << i << std::endl;
        }

        size_t predicted = std::distance(
            result.begin(),
            std::max_element(result.begin(), result.end())
        );

        size_t actual = std::distance(
            testData.labels[i].begin(),
            std::max_element(
                testData.labels[i].begin(),
                testData.labels[i].end()
            )
        );

        if (predicted == actual) {
            correct++;
        }
    }

    std::println("Correct: {}", correct);
    std::println("testPass: {}", testData.images.size());

    double testAccuracy = 100.0 * correct / testData.images.size();
    std::println("Test accuracy: {}", testAccuracy);

    std::cout << "Accuracy: "
        << ((double)correct * 100.0) / testData.images.size() 
        << "%" << std::endl;
}

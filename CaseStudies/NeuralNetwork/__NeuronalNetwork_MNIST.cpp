#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <cstdint>
#include <numeric>

namespace Tutorial_David_Miller_Using_MNIST {

    using namespace std;

    // -------------------------
    // David Miller style network
    // -------------------------

    struct Connection {
        double weight;
        double deltaWeight;
    };

    class Neuron;

    typedef vector<Neuron> Layer;

    // Hyperparameter wie im Tutorial:
    static double eta = 0.15; // learning rate
    static double alpha = 0.5;  // momentum

    class Neuron {
    public:
        Neuron(unsigned numOutputs, unsigned myIndex);

        void setOutputVal(double val) { m_outputVal = val; }
        double getOutputVal() const { return m_outputVal; }

        void feedForward(const Layer& prevLayer);
        void calcOutputGradients(double targetVal);
        void calcHiddenGradients(const Layer& nextLayer);
        void updateInputWeights(Layer& prevLayer);

    private:
        static double transferFunction(double x);
        static double transferFunctionDerivative(double x);
        static double randomWeight() { return rand() / double(RAND_MAX); }

        double sumDOW(const Layer& nextLayer) const;

        double m_outputVal = 0.0;
        vector<Connection> m_outputWeights;
        unsigned m_myIndex = 0;
        double m_gradient = 0.0;
    };

    class Net {
    public:
        Net(const vector<unsigned>& topology);

        void feedForward(const vector<double>& inputVals);
        void backProp(const vector<double>& targetVals);

        void getResults(vector<double>& resultVals) const;

        double getRecentAverageError() const { return m_recentAverageError; }

    private:
        vector<Layer> m_layers;
        double m_error = 0.0;

        double m_recentAverageError = 0.0;
        double m_recentAverageSmoothingFactor = 100.0;
    };

    Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
        : m_myIndex(myIndex)
    {
        for (unsigned c = 0; c < numOutputs; ++c) {
            m_outputWeights.push_back(Connection());
            m_outputWeights.back().weight = randomWeight();
            m_outputWeights.back().deltaWeight = 0.0;
        }
    }

    double Neuron::transferFunction(double x) {
        // David Miller: tanh
        return tanh(x);
    }

    double Neuron::transferFunctionDerivative(double x) {
        // x ist bereits outputVal, daher: 1 - x^2
        return 1.0 - x * x;
    }

    void Neuron::feedForward(const Layer& prevLayer) {
        double sum = 0.0;

        for (unsigned n = 0; n < prevLayer.size(); ++n) {
            sum += prevLayer[n].getOutputVal() *
                prevLayer[n].m_outputWeights[m_myIndex].weight;
        }

        m_outputVal = Neuron::transferFunction(sum);
    }

    void Neuron::calcOutputGradients(double targetVal) {
        double delta = targetVal - m_outputVal;
        m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
    }

    double Neuron::sumDOW(const Layer& nextLayer) const {
        double sum = 0.0;

        // Bias-Neuron in nextLayer ignorieren -> size()-1
        for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
            sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
        }
        return sum;
    }

    void Neuron::calcHiddenGradients(const Layer& nextLayer) {
        double dow = sumDOW(nextLayer);
        m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
    }

    void Neuron::updateInputWeights(Layer& prevLayer) {
        for (unsigned n = 0; n < prevLayer.size(); ++n) {
            Neuron& neuron = prevLayer[n];
            double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

            double newDeltaWeight =
                eta * neuron.getOutputVal() * m_gradient +
                alpha * oldDeltaWeight;

            neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
            neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
        }
    }

    Net::Net(const vector<unsigned>& topology) {
        unsigned numLayers = (unsigned int) topology.size();

        for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
            m_layers.push_back(Layer());

            unsigned numOutputs = (layerNum == topology.size() - 1)
                ? 0
                : topology[layerNum + 1];

            // +1 Bias-Neuron pro Layer
            for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
                m_layers.back().push_back(Neuron(numOutputs, neuronNum));
            }

            // Bias output auf 1.0 setzen
            m_layers.back().back().setOutputVal(1.0);
        }
    }

    void Net::feedForward(const vector<double>& inputVals) {
        assert(inputVals.size() == m_layers[0].size() - 1);

        for (unsigned i = 0; i < inputVals.size(); ++i) {
            m_layers[0][i].setOutputVal(inputVals[i]);
        }

        for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
            Layer& prevLayer = m_layers[layerNum - 1];

            for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) {
                m_layers[layerNum][n].feedForward(prevLayer);
            }

            // Bias bleibt 1.0
            m_layers[layerNum].back().setOutputVal(1.0);
        }
    }

    void Net::backProp(const vector<double>& targetVals) {
        Layer& outputLayer = m_layers.back();
        assert(targetVals.size() == outputLayer.size() - 1);

        // RMS error
        m_error = 0.0;
        for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
            double delta = targetVals[n] - outputLayer[n].getOutputVal();
            m_error += delta * delta;
        }
        m_error /= (outputLayer.size() - 1);
        m_error = sqrt(m_error);

        // recent average error
        m_recentAverageError =
            (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) /
            (m_recentAverageSmoothingFactor + 1.0);

        // Output gradients
        for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
            outputLayer[n].calcOutputGradients(targetVals[n]);
        }

        // Hidden gradients
        for (unsigned layerNum = (unsigned int)m_layers.size() - 2; layerNum > 0; --layerNum) {
            Layer& hiddenLayer = m_layers[layerNum];
            Layer& nextLayer = m_layers[layerNum + 1];

            for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
                hiddenLayer[n].calcHiddenGradients(nextLayer);
            }
        }

        // Update weights
        for (unsigned layerNum = (unsigned int)m_layers.size() - 1; layerNum > 0; --layerNum) {
            Layer& layer = m_layers[layerNum];
            Layer& prevLayer = m_layers[layerNum - 1];

            for (unsigned n = 0; n < layer.size() - 1; ++n) {
                layer[n].updateInputWeights(prevLayer);
            }
        }
    }

    void Net::getResults(vector<double>& resultVals) const {
        resultVals.clear();

        for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
            resultVals.push_back(m_layers.back()[n].getOutputVal());
        }
    }

    // -------------------------
    // MNIST Loader (IDX format)
    // -------------------------

    static uint32_t readBE32(ifstream& in) {
        unsigned char bytes[4];
        in.read(reinterpret_cast<char*>(bytes), 4);
        return (uint32_t(bytes[0]) << 24) |
            (uint32_t(bytes[1]) << 16) |
            (uint32_t(bytes[2]) << 8) |
            (uint32_t(bytes[3]));
    }

    struct MNISTDataset {
        vector<vector<double>> images; // normalized [-1..+1] or [0..1]
        vector<uint8_t> labels;
        int rows = 0;
        int cols = 0;
    };

    static MNISTDataset loadMNIST(const string& imagesPath, const string& labelsPath, bool normalizeToTanhRange = true) {
        MNISTDataset ds;

        // Labels
        ifstream lbl(labelsPath, ios::binary);
        if (!lbl) {
            throw runtime_error("Cannot open labels file: " + labelsPath);
        }
        uint32_t magicLbl = readBE32(lbl);
        uint32_t numLbl = readBE32(lbl);
        if (magicLbl != 2049) {
            throw runtime_error("Invalid labels magic number (expected 2049)");
        }

        ds.labels.resize(numLbl);
        lbl.read(reinterpret_cast<char*>(ds.labels.data()), numLbl);

        // Images
        ifstream img(imagesPath, ios::binary);
        if (!img) {
            throw runtime_error("Cannot open images file: " + imagesPath);
        }
        uint32_t magicImg = readBE32(img);
        uint32_t numImg = readBE32(img);
        uint32_t rows = readBE32(img);
        uint32_t cols = readBE32(img);

        if (magicImg != 2051) {
            throw runtime_error("Invalid images magic number (expected 2051)");
        }
        if (numImg != numLbl) {
            throw runtime_error("Image count != label count");
        }

        ds.rows = int(rows);
        ds.cols = int(cols);

        const int imageSize = int(rows * cols);
        ds.images.resize(numImg, vector<double>(imageSize));

        vector<uint8_t> buffer(imageSize);

        for (uint32_t i = 0; i < numImg; ++i) {
            img.read(reinterpret_cast<char*>(buffer.data()), imageSize);

            for (int p = 0; p < imageSize; ++p) {
                double v = double(buffer[p]) / 255.0; // [0..1]

                if (normalizeToTanhRange) {
                    // tanh passt besser mit Inputs in [-1..+1]
                    v = v * 2.0 - 1.0;
                }

                ds.images[i][p] = v;
            }
        }

        return ds;
    }

    // One-hot target vector für 10 Klassen
    static vector<double> makeOneHot(uint8_t label, int numClasses = 10, bool tanhTargets = true) {
        vector<double> t(numClasses, tanhTargets ? -1.0 : 0.0);

        // Für tanh Output: -1 für "false", +1 für "true"
        t[label] = tanhTargets ? 1.0 : 1.0;
        return t;
    }

    static int argmax(const vector<double>& v) {
        return int(max_element(v.begin(), v.end()) - v.begin());
    }

    static void main_neural_net_mnist()
    {
        srand(0);

        // ---- Paths (anpassen oder per argv übergeben) ----
        // Du brauchst diese Dateien im gleichen Ordner oder mit Pfad:
        // train-images-idx3-ubyte
        // train-labels-idx1-ubyte
        // t10k-images-idx3-ubyte
        // t10k-labels-idx1-ubyte

        string trainImages = "../Resources/train-images-idx3-ubyte";
        string trainLabels = "../Resources/train-labels-idx1-ubyte";
        string testImages = "../Resources/t10k-images-idx3-ubyte";
        string testLabels = "../Resources/t10k-labels-idx1-ubyte";

        // 
        //if (argc == 5) {
        //    trainImages = argv[1];
        //    trainLabels = argv[2];
        //    testImages = argv[3];
        //    testLabels = argv[4];
        //}
        //else {
        //    cout << "Usage (optional): " << argv[0]
        //        << " train-images train-labels test-images test-labels\n";
        //    cout << "Using default filenames in current directory.\n\n";
        //}

        // ---- Load MNIST ----
        cout << "Loading MNIST...\n";
        MNISTDataset train = loadMNIST(trainImages, trainLabels, true);
        MNISTDataset test = loadMNIST(testImages, testLabels, true);

        cout << "Train samples: " << train.images.size() << "\n";
        cout << "Test  samples: " << test.images.size() << "\n";
        cout << "Image size: " << train.rows << "x" << train.cols << " = " << train.rows * train.cols << "\n\n";

        // ---- Build Network Topology ----
        // 784 -> 128 -> 64 -> 10 (Bias automatisch pro Layer)
        vector<unsigned> topology;
        topology.push_back(train.rows * train.cols); // 784
        topology.push_back(128);
        topology.push_back(64);
        topology.push_back(10);

        Net myNet(topology);

        // ---- Training loop ----
        cout << "Training...\n";

        vector<int> indices(train.images.size());
        std::iota(indices.begin(), indices.end(), 0);

        std::mt19937 rng(0);

        int epochs = 3;                // für schnelle Tests klein lassen
        int reportEvery = 2000;

        for (int e = 1; e <= epochs; ++e) {
            shuffle(indices.begin(), indices.end(), rng);

            int correct = 0;

            for (size_t i = 0; i < indices.size(); ++i) {
                int idx = indices[i];

                const vector<double>& inputVals = train.images[idx];
                uint8_t label = train.labels[idx];

                vector<double> targetVals = makeOneHot(label, 10, true);

                myNet.feedForward(inputVals);
                myNet.backProp(targetVals);

                vector<double> resultVals;
                myNet.getResults(resultVals);

                int pred = argmax(resultVals);
                if (pred == int(label)) correct++;

                if ((int(i) + 1) % reportEvery == 0) {
                    double acc = 100.0 * correct / double(i + 1);
                    cout << "Epoch " << e
                        << " | step " << (i + 1) << "/" << indices.size()
                        << " | train acc: " << acc << "% "
                        << " | avg error: " << myNet.getRecentAverageError()
                        << "\n";
                }
            }

            double epochAcc = 100.0 * correct / double(indices.size());
            cout << "Epoch " << e << " finished. Train accuracy: " << epochAcc << "%\n\n";
        }

        // ---- Test loop ----
        cout << "Testing...\n";
        int correctTest = 0;

        for (size_t i = 0; i < test.images.size(); ++i) {
            myNet.feedForward(test.images[i]);

            vector<double> resultVals;
            myNet.getResults(resultVals);

            int pred = argmax(resultVals);
            if (pred == int(test.labels[i])) correctTest++;
        }

        double testAcc = 100.0 * correctTest / double(test.images.size());
        cout << "Test accuracy: " << testAcc << "%\n";
    }

}

static void main_neural_net_mnist()
{
    Tutorial_David_Miller_Using_MNIST::main_neural_net_mnist();
}

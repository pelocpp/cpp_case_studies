// =====================================================================================
// TrainingAndTestData_MNIST.cpp
// =====================================================================================

#include "Common.h"
#include "TrainingAndTestData_MNIST.h"

#include <fstream>
#include <print>
#include <sstream>

constexpr std::size_t MaxIterations = 1000;

TrainingAndTestData_MNIST::TrainingAndTestData_MNIST()
    : m_topology{ 28 * 28, 100, 10 }, m_imagesTrainingIndex{}, m_imagesTestIndex{}
{
}

const Topology& TrainingAndTestData_MNIST::getTopology()
{
    return m_topology;
}

void TrainingAndTestData_MNIST::setFilenames(
    const std::string& imagesTrainingFilename,
    const std::string& labelsTrainingFilename,
    const std::string& imagesTestFilename,
    const std::string& labelsTestFilename)
{
    m_imagesTrainingFilename = imagesTrainingFilename;
    m_labelsTrainingFilename = labelsTrainingFilename;
    m_imagesTestFilename = imagesTestFilename;
    m_labelsTestFilename = labelsTestFilename;
}

static std::uint32_t readInt(std::ifstream& file)
{
    std::uint8_t bytes[4]{};
    file.read((char*) bytes, 4);

    // convert value from big-endian to native endianness
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

void TrainingAndTestData_MNIST::loadData()
{
    loadTrainingData();
    loadTestData();
}

void TrainingAndTestData_MNIST::loadTrainingData()
{
    std::println("Loading Training Data ...");

    std::ifstream imagesTrainingFile;
    imagesTrainingFile.open(m_imagesTrainingFilename.c_str(), std::ios::binary);
    if (!imagesTrainingFile.is_open()) {
        throw std::invalid_argument("Wrong images training filename");
    }

    std::ifstream labelsTrainingFile;
    labelsTrainingFile.open(m_labelsTrainingFilename.c_str(), std::ios::binary);
    if (!labelsTrainingFile.is_open()) {
        throw std::invalid_argument("Wrong images test filename");
    }

    std::uint32_t magicNumberImages{ readInt(imagesTrainingFile) };
    std::uint32_t numImages{ readInt(imagesTrainingFile) };
    std::uint32_t rows{ readInt(imagesTrainingFile) };
    std::uint32_t cols{ readInt(imagesTrainingFile) };

    std::uint32_t magicNumberLabels{ readInt(labelsTrainingFile) };
    std::uint32_t numLabels{ readInt(labelsTrainingFile) };

    if (numImages != numLabels) {
        throw std::runtime_error("Number of training images and labels do not match!");
    }

    if (magicNumberImages != 2051) {
        throw std::runtime_error("Invalid training images magic number (expected 2051)");
    }

    if (magicNumberLabels != 2049) {
        throw std::runtime_error("Invalid training labels magic number (expected 2049)");
    }

    if (rows != 28) {
        throw std::runtime_error("Wrong number of training rows (expected 28)");
    }

    if (cols != 28) {
        throw std::runtime_error("Wrong number of training cols (expected 28)");
    }

    const std::uint32_t imageSize{ rows * cols };  // 28 * 28

    m_imagesTraining.resize(numImages, std::vector<double>(imageSize));
    m_labelsTraining.resize(numImages);

    std::vector<std::uint8_t> buffer(imageSize);
    std::uint8_t label{};

    for (std::uint32_t i{}; i != numImages; ++i)
    {
        imagesTrainingFile.read(reinterpret_cast<char*>(buffer.data()), imageSize);

        std::vector<double> rawImage(imageSize);
        for (std::uint32_t j{}; j != imageSize; ++j)
        {
            double pixel{ static_cast<double>(buffer[j]) / 255.0 };   // [0.0 .. 1.0]
            pixel = pixel * 2.0 - 1.0;    // normalize to [-1.0, 1.0] (std::tanh prefers this range)
            m_imagesTraining[i][j] = pixel;
        }

        labelsTrainingFile.read((char*) &label, 1);
        std::vector<double> target(10, -1.0);
        target[label] = 1.0; // One-Hot encoding: std::tanh normalizes into [-1.0, 1.0]
        m_labelsTraining[i] = target;
    }

    imagesTrainingFile.close();
    labelsTrainingFile.close();

    std::println("Loading Training Data done.");
}


void TrainingAndTestData_MNIST::loadTestData()
{
    std::println("Loading Test Data ...");

    std::ifstream imagesTestFile;
    imagesTestFile.open(m_imagesTestFilename.c_str(), std::ios::binary);
    if (!imagesTestFile.is_open()) {
        throw std::invalid_argument("Wrong labels training filename");
    }

    std::ifstream labelsTestFile;
    labelsTestFile.open(m_labelsTestFilename.c_str(), std::ios::binary);
    if (!labelsTestFile.is_open()) {
        throw std::invalid_argument("Wrong labels test filename");
    }

    std::uint32_t magicNumberImages {readInt(imagesTestFile) };
    std::uint32_t numImages{ readInt(imagesTestFile) };
    std::uint32_t rows{ readInt(imagesTestFile) };
    std::uint32_t cols{ readInt(imagesTestFile) };

    std::uint32_t magicNumberLabels {readInt(labelsTestFile) };
    std::uint32_t numLabels {readInt(labelsTestFile) };

    if (numImages != numLabels) {
        throw std::runtime_error("Number of test images and labels do not match!");
    }

    if (magicNumberImages != 2051) {
        throw std::runtime_error("Invalid test images magic number (expected 2051)");
    }

    if (magicNumberLabels != 2049) {
        throw std::runtime_error("Invalid test labels magic number (expected 2049)");
    }

    if (rows != 28) {
        throw std::runtime_error("Wrong number of test rows (expected 28)");
    }

    if (cols != 28) {
        throw std::runtime_error("Wrong number of test  cols (expected 28)");
    }

    const std::uint32_t imageSize{ rows * cols };  // 28 * 28

    m_imagesTest.resize(numLabels, std::vector<double>(imageSize));
    m_labelsTest.resize(numLabels);

    std::vector<std::uint8_t> buffer(imageSize);
    std::uint8_t label{};

    for (std::uint32_t i{}; i != numLabels; ++i)
    {
        imagesTestFile.read(reinterpret_cast<char*>(buffer.data()), imageSize);

        std::vector<double> rawImage(imageSize);
        for (std::uint32_t j{}; j != imageSize; ++j)
        {
            double pixel{ static_cast<double>(buffer[j]) / 255.0 };   // [0.0 .. 1.0]
            pixel = pixel * 2.0 - 1.0; // normalize to [-1.0, 1.0] (std::tanh prefers this range)
            m_imagesTest[i][j] = pixel;
        }

        labelsTestFile.read((char*)&label, 1);
        std::vector<double> target(10, -1.0);
        target[label] = 1.0; // One-Hot encoding: std::tanh normalizes into [-1.0, 1.0]
        m_labelsTest[i] = target;
    }

    imagesTestFile.close();
    labelsTestFile.close();

    std::println("Loading Test Data done.");
}

bool TrainingAndTestData_MNIST::isEndOfTrainingData() const 
{
     return m_imagesTrainingIndex >= m_imagesTraining.size();

    // TBD: ÄNDERN !!!
  // return m_imagesTrainingIndex >= MaxIterations;
}

void TrainingAndTestData_MNIST::advanceTraining()
{
    ++ m_imagesTrainingIndex;
}

bool TrainingAndTestData_MNIST::isEndOfTestData() const
{
    // TBD: ÄNDERN !!!
   return m_imagesTestIndex >= m_imagesTest.size();
   // return m_imagesTestIndex >= MaxIterations;
}

void TrainingAndTestData_MNIST::advanceTest()
{
    ++m_imagesTestIndex;
}

const std::vector<double>& TrainingAndTestData_MNIST::nextTrainingInput() const
{
    return m_imagesTraining[m_imagesTrainingIndex];
}

const std::vector<double>& TrainingAndTestData_MNIST::nextTrainingTargetOutput() const
{
    return m_labelsTraining[m_imagesTrainingIndex];
}

const std::vector<double>& TrainingAndTestData_MNIST::nextTestInput() const
{
    return m_imagesTest[m_imagesTestIndex];
}

const std::vector<double>& TrainingAndTestData_MNIST::nextTestTargetOutput() const
{
    return m_labelsTest[m_imagesTestIndex];
}

// =====================================================================================
// End-of-File
// =====================================================================================

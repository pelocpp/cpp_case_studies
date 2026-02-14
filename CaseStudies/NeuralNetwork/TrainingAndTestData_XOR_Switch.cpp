// =====================================================================================
// TrainingAndTestData_XOR_Switch.cpp
// =====================================================================================

#include "Common.h"
#include "TrainingAndTestData_XOR_Switch.h"

#include <filesystem>
#include <fstream>
#include <print>
#include <sstream>

TrainingAndTestData_XOR_Switch::TrainingAndTestData_XOR_Switch()
    : m_topology{ 2, 4, 1 }, m_xorTrainingIndex{}, m_xorTestIndex{}
{
}

void TrainingAndTestData_XOR_Switch::setFilenames(const std::string& trainingFilename, const std::string& testFilename)
{
    m_trainingFilename = trainingFilename;
    m_testFilename = testFilename;
}

const Topology& TrainingAndTestData_XOR_Switch::getTopology()
{
    return m_topology;
}

bool TrainingAndTestData_XOR_Switch::isEndOfTrainingData() const
{
    return m_xorTrainingIndex >= m_xorTraining.size();
}

void TrainingAndTestData_XOR_Switch::advanceTraining()
{
    ++m_xorTrainingIndex;
}

bool TrainingAndTestData_XOR_Switch::isEndOfTestData() const
{
    return m_xorTestIndex >= m_xorTest.size();
}

void TrainingAndTestData_XOR_Switch::advanceTest()
{
    ++m_xorTestIndex;
}

void TrainingAndTestData_XOR_Switch::loadData()
{
    loadTrainingData();
    loadTestData();
}

void TrainingAndTestData_XOR_Switch::loadTrainingData()
{
    std::println("Loading Training Data ...");

    std::filesystem::path path{ std::filesystem::current_path() };
    m_trainingFilename = path.string() + "\\Resources\\" + m_trainingFilename;
    std::ifstream xorTrainingFile;
    xorTrainingFile.open(m_trainingFilename.c_str());
    if (!xorTrainingFile.is_open()) {
        throw std::invalid_argument("Wrong XOR training filename");
    }

    while (! xorTrainingFile.eof()) {

        // neural network input 
        std::string line{};
        getline(xorTrainingFile, line);
        std::stringstream ss{ line };

        std::vector<double> xorGate(2);
        std::string label{};

        ss >> label;
        if (label.compare("in:") == 0) {
            double value{};
            std::size_t i{};
            while (ss >> value) {
                xorGate[i] = value;
                ++i;
            }
        }
        m_xorTraining.push_back(std::move(xorGate));

        // neural network target
        getline(xorTrainingFile, line);
        ss.str(line);
        ss.clear();   // clear all error state flags
        ss.seekg(0);  // set input position indicator to the beginning of this string stream object

        ss >> label;
        if (label.compare("out:") == 0) {
            double value{};
            ss >> value;
            std::vector<double> result(1);
            result[0] = value;
            m_xorTrainingTarget.push_back(result);
        }
    }

    xorTrainingFile.close();

    std::println("Loading Training Data done.");
}

void TrainingAndTestData_XOR_Switch::loadTestData()
{
    std::println("Loading Test Data ...");

    std::filesystem::path path{ std::filesystem::current_path() };
    m_testFilename = path.string() + "\\Resources\\" + m_testFilename;
    std::ifstream xorTestFile;
    xorTestFile.open(m_testFilename.c_str());
    if (!xorTestFile.is_open()) {
        throw std::invalid_argument("Wrong XOR training filename");
    }

    while (!xorTestFile.eof()) {

        // neural network input 
        std::string line{};
        getline(xorTestFile, line);
        std::stringstream ss{ line };

        std::vector<double> xorGate(2);
        std::string label{};

        ss >> label;
        if (label.compare("in:") == 0) {
            double value{};
            std::size_t i{};
            while (ss >> value) {
                xorGate[i] = value;
                ++i;
            }
        }
        m_xorTest.push_back(std::move(xorGate));

        // neural network target
        getline(xorTestFile, line);
        ss.str(line);
        ss.clear();   // clear all error state flags
        ss.seekg(0);  // set input position indicator to the beginning of this string stream object

        ss >> label;
        if (label.compare("out:") == 0) {
            double value{};
            ss >> value;
            std::vector<double> result(1);
            result[0] = value;
            m_xorTestTarget.push_back(result);
        }
    }

    xorTestFile.close();

    std::println("Loading Training Data done.");
}

const std::vector<double>& TrainingAndTestData_XOR_Switch::nextTrainingInput() const
{
    return m_xorTraining[m_xorTrainingIndex];
}

const std::vector<double>& TrainingAndTestData_XOR_Switch::nextTrainingTargetOutput() const
{
    return m_xorTrainingTarget[m_xorTrainingIndex];
}

const std::vector<double>& TrainingAndTestData_XOR_Switch::nextTestInput() const
{
    return m_xorTest[m_xorTestIndex];
}

const std::vector<double>& TrainingAndTestData_XOR_Switch::nextTestTargetOutput() const
{
    return m_xorTestTarget[m_xorTestIndex];
}

// =====================================================================================
// End-of-File
// =====================================================================================

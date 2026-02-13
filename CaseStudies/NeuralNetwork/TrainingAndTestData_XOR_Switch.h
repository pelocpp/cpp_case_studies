// =====================================================================================
// TrainingAndTestData_XOR_Switch.h
// =====================================================================================

#pragma once

#include "Common.h"

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

class TrainingAndTestData_XOR_Switch
{
public:
    // c'tor(s)
    TrainingAndTestData_XOR_Switch();

    // getter / setter
    void setFilenames(
        const std::string& trainingFilename,
        const std::string& testFilename
    );

    // public interface
    const Topology& getTopology();
    void loadData();
    bool isEndOfTrainingData() const;
    void advanceTraining();
    bool isEndOfTestData() const;
    void advanceTest();

    // returns the number of values
    const std::vector<double>& nextTrainingInput() const;
    const std::vector<double>& nextTrainingTargetOutput() const;
    const std::vector<double>& nextTestInput() const;
    const std::vector<double>& nextTestTargetOutput() const;

private:
    // helper methods
    void loadTrainingData();
    void loadTestData();

private:
    Topology    m_topology;

    std::string m_trainingFilename;
    std::string m_testFilename;

    std::vector<std::vector<double>> m_xorTraining;
    std::vector<std::vector<double>> m_xorTrainingTarget;
    std::vector<std::vector<double>> m_xorTest;
    std::vector<std::vector<double>> m_xorTestTarget;

    std::size_t m_xorTrainingIndex;
    std::size_t m_xorTestIndex;
};

// =====================================================================================
// End-of-File
// =====================================================================================

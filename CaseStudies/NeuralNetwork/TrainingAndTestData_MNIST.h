// =====================================================================================
// TrainingAndTestData_MNIST.h
// =====================================================================================

#pragma once

#include "Common.h"

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

class TrainingAndTestData_MNIST
{
public:
    // c'tor(s)
    TrainingAndTestData_MNIST     ();

    // getter / setter
    void setFilenames             (
        const std::string& imagesTrainingFilename,
        const std::string& labelsTrainingFilename,
        const std::string& imagesTestFilename,
        const std::string& labelsTestFilename
    );
    
    // public interface
    const Topology& getTopology  ();
    void loadData                ();
    bool isEndOfTrainingData     () const;
    void advanceTraining         ();
    bool isEndOfTestData         () const;
    void advanceTest             ();

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

    std::string m_imagesTrainingFilename;
    std::string m_labelsTrainingFilename;
    std::string m_imagesTestFilename;
    std::string m_labelsTestFilename;

    std::vector<std::vector<double>> m_imagesTraining;
    std::vector<std::vector<double>> m_labelsTraining;
    std::vector<std::vector<double>> m_imagesTest;
    std::vector<std::vector<double>> m_labelsTest;

    std::size_t m_imagesTrainingIndex;
    std::size_t m_imagesTestIndex;
};

// =====================================================================================
// End-of-File
// =====================================================================================


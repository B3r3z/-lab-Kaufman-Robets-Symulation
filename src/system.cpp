#include "system.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  // Include this for std::fixed and std::setprecision

void System::addStream(Stream stream) {
    _streams.push_back(stream);
}
void System::calculate() {

}

void System::calculateSumOfA() {
    double baseSumOfA = ((_aMax - _aMin) / (_step + 1.0)) * ((_aMin + _aMax) / 2.0);
    baseSumOfA *= _capacity;  // Base calculation using capacity

    for (auto& _stream : _streams) {
        double tmp = _stream.getT();
        if (tmp == 0) {
            std::cerr << "Error: Division by zero encountered in calculateSumOfA for stream." << std::endl;
            continue;  // Skip this stream to avoid division by zero
        }
        double streamSpecificSumOfA = baseSumOfA / tmp;  // Calculate specific sumOfA for this stream
        _stream.setAvrageA(streamSpecificSumOfA);  // Set the specific average for this stream
    }
}

void System::calculateSumOfElements() {
    //double totalSum = 0.0;
    double innerSum = 1.0;  // Start with SUM(0) = 1
    int m = _capacity;  // Number of streams

    for (int n = 1; n <= m; ++n) {  // Start from 1 to avoid division by zero
        double currentSum = 0.0;
        for (const auto& _stream : _streams) {
            currentSum += _stream.getAvrageA() * _stream.getT();
        }
        innerSum = (1.0 / n) * currentSum * innerSum;  // Recursive calculation
    }

    _totalSum = innerSum;
} 
void System::saveResultsToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Write headers
    file << "a;            p1,         p2,         ...,           pn" << std::endl;  // Add spaces in the header

    double a = _aMin;
    file << std::fixed << std::setprecision(6);  // Set fixed-point notation with 6 decimal places
    for (const auto& resultRow : _results) {
        file << a << ";         ";  // Add spaces after 'a' and semicolon
        for (size_t i = 0; i < resultRow.size(); ++i) {
            file << resultRow[i];
            if (i < resultRow.size() - 1) {
                file << ",         ";  // Add spaces after each comma
            }
        }
        file << std::endl;
        a += _step;
    }

    file.close();
}

void System::calcProbability() {
    if (_totalSum == 0) {
        std::cerr << "Error: _totalSum is zero, cannot calculate probabilities." << std::endl;
        return;
    }
    int m = _capacity;  // Number of streams
    _results.resize(m);  // Ensure _results has enough space for m elements
    for (int n = 1; n <= m; ++n) {  // Start from 1 to avoid division by zero
        double innerSum = 1.0;  // Reset innerSum for each n
        double currentSum = 0.0;
        std::vector<double> vectorOfProbability;  // Create a new vector for each n
        for (const auto& _stream : _streams) {
            currentSum += _stream.getAvrageA() * _stream.getT();
            innerSum = (1.0 / n) * currentSum * innerSum; 
            vectorOfProbability.push_back(innerSum/_totalSum);
        }
        _results[n - 1] =vectorOfProbability;  // Adjust index if _results is zero-indexed
    }
}

void System::printResults() const{
        double a = _aMin;
    for (const auto& resultRow : _results) {
        std::cout << a;
        for (const auto& result : resultRow) {
            std::cout << " " << result;
        }
        std::cout << std::endl;
        a += _step;
    }
}

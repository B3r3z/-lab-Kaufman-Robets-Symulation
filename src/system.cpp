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
    double baseSumOfA = (_step*(_aMax+_aMin) + _aMax*_aMax - _aMin*_aMin)/(2*_step); // arytmet. sum of A
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
    _sumOfA = baseSumOfA;
}

void System::calculateSumOfElements() {
}

void System::calcProbability() {

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

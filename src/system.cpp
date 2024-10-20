#include "system.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  // Include this for std::fixed and std::setprecision

void System::addStream(Stream stream) {
    _streams.push_back(stream);
}

void System::calculateAverageInputOfStream() {
    double baseSumOfA = (_step*(_aMax+_aMin) + _aMax*_aMax - _aMin*_aMin)/(2*_step); // arytmet. sum of A
    baseSumOfA *= _capacity / _streams.size();  // Base calculation using capacity and number of streams
    for (auto& _stream : _streams) {
        double tmp = _stream.getT();
        if (tmp == 0) {
                std::cerr << "Error: Division by zero encountered in calculateAverageInputOfStream for stream." << std::endl;
        }
        double streamSpecificSumOfA = baseSumOfA / tmp;  // Calculate specific sumOfA for this stream
        _stream.setAvrageA(streamSpecificSumOfA);  // Set the specific average for this stream
    }
    _sumOfA = baseSumOfA;
}

double System::calculateSUM() {
    double sum = 1.0;
    for (int i  = 1; i <= _streams.size()+1; i++) {
        sum += 1/i;
    }
    sum *= _sumOfA * _streams.size(); // sum of a * capacity / number of streams
    return sum;
}

void System::calculateProbability() {
    double Pn = 0.0;
    double sum=1.0;
    double Omega = calculateSUM();
    for (int i = 1; i < 1 + _streams.size(); i++) {
        sum += 1/i;
        Pn += sum/Omega;
        _streams[i].setProbability(Pn); 
    }
    
}

////void System::saveResultsToFile(const std::string& filename) const {
//    std::ofstream file(filename);
//    if (!file.is_open()) {
//        std::cerr << "Failed to open file: " << filename << std::endl;
//        return;
//    }
//
//    // Write headers
//    file << "a;            p1,         p2,         ...,           pn" << std::endl;  // Add spaces in the header
//
//    double a = _aMin;
//    file << std::fixed << std::setprecision(6);  // Set fixed-point notation with 6 decimal places
//    for (const auto& resultRow : _results) {
//        file << a << ";         ";  // Add spaces after 'a' and semicolon
//        for (size_t i = 0; i < resultRow.size(); ++i) {
//            file << resultRow[i];
//            if (i < resultRow.size() - 1) {
//                file << ",         ";  // Add spaces after each comma
//            }
//        }
//        file << std::endl;
//        a += _step;
//    }
//
//    file.close();
//}
//
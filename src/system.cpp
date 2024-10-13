#include "system.hpp"
#include <iostream>
#include <fstream>
#include <string>

void System::addStream(Stream stream) {
    _streams.push_back(stream);
}

void System::calculate() {
    _results.clear();  // Clear previous results
    int m = _streams.size();  // Number of stream classes
    double sum=0;
    std::vector<double> currentResults;
    for (double a = _aMin; a <= _aMax; a += _step) {
        for (const auto& stream : _streams) {
            double t_i = stream.getT();
            double a_i = (a * _capacity) / m*;            
            currentResults.push_back(a_i);  // Store the result for this stream
        }
        //_results.push_back(currentResults);  // Store results for this value of a
    }
    double tmp = 1;
    currentResults[1]=currentResults[1]*tmp;
 
    for(int i=2; i<=_capacity; i++){
        currentResults[i]=(1/i)*(tmp+currentResults[i]*tmp);
        tmp =currentResults[i];
    }

    double P=0;
    for(int i=0; i<_capacity; i++){
        P+=currentResults=
    }


    _results.push_back(currentResults);  // Store results for this value of a
}

void System::saveResultsToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    double a = _aMin;
    for (const auto& resultRow : _results) {
        file << a;
        for (const auto& result : resultRow) {
            file << " " << result;
        }
        file << std::endl;
        a += _step;
    }

    file.close();
}

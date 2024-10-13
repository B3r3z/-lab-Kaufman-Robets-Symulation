#pragma once
#include "stream.hpp"
#include <vector>
#include <string>
class System {
public:
    System(int capacity, double aMin, double aMax, double step = 0.1)
        : _capacity(capacity), _aMin(aMin), _aMax(aMax), _step(step) {};
    ~System() {};
    void addStream(Stream stream);
    void calculate();
    const std::vector<std::vector<double>>& getResults() const { return _results; }  // Getter for results
    void saveResultsToFile(const std::string& filename) const;

private:
    std::vector<Stream> _streams;
    int _capacity;
    double _aMin;
    double _aMax;
    double _step;
    std::vector<std::vector<double>> _results;  // 2D vector to store results
};

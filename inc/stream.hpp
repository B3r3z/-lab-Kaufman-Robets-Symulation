#pragma once
#include <vector>


class Stream {
public:
    Stream(double T):  _T(T){};
    Stream(double T, double avrageA):  _T(T), _avrageA(avrageA){};
    void setAvrageA(double inAvrageA){_avrageA = inAvrageA;};
    double getAvrageA() const {return _avrageA;};
    void setProbability(double inProbability){_probability = inProbability;};
    double getProbability() const {return _probability;};
    ~Stream(){};
    double getT() const { return _T; };
private:
 //   double _aMin;
 //   double _aMax;
    double _T;
    double _avrageA;
    double _probability;
};
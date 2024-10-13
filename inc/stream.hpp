#pragma once
#include <vector>


class Stream {
public:
    Stream(double T):  _T(T){};
    ~Stream(){};
    double getT() const { return _T; };
private:
 //   double _aMin;
 //   double _aMax;
    double _T;
};
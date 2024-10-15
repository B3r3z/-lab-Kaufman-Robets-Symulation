#include "system.hpp"
#include "stream.hpp"
#include <iostream>

int main() {
    int m, capacity, a;
    double inAmin, inAmax, inT;
    std::cout << "Podaj pojemność systemu: ";
    std::cin >> capacity;
    std::cout << "Podaj dolną granicę a: ";
    std::cin >> inAmin;
    std::cout << "Podaj górną granicę a: ";
    std::cin >> inAmax;
    System system(capacity, inAmin, inAmax);
    
    std::cout << "Podaj liczbę strumieni do utworzenia: ";
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        std::cout << "Podaj parametry strumienia " << i + 1 << ": ";
        std::cin >> inT;
        system.addStream(Stream(inT));
    }
    system.calculateSumOfA();
    system.calculateSumOfElements();
    system.calcProbability();
 //   system.calculate();
    system.saveResultsToFile("results.txt");
    system.printResults();
    std::cout<<"TS: " << system.getTotalSum();

    return 0;
}

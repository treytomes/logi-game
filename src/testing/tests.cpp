#include <exception>
#include <iostream>
using namespace std;

// TODO: Cost is related to computational complexity.

#include "testing/TestSuite.h"

#include "testing/CircuitTests.h"
#include "testing/PerceptronTests.h"

int main(int argc, char* argv[]) {
    try {
        TestSuite* tests;
        
        tests = new PerceptronTests();
        tests->runAll();
        delete tests;

        tests = new CircuitTests();
        tests->runAll();
        delete tests;
    } catch (exception& e) {
        cerr << "An error occurred." << endl;
        cerr << e.what() << endl;
    }
    return 0;
}

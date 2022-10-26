#ifndef __TESTSUITEBASE_H__
#define __TESTSUITEBASE_H__

#include <exception>
#include <iostream>
#include <string>
using namespace std;

#include "TestSuite.h"

template<typename TDerivedClass>
class TestSuiteBase: public TestSuite {
    protected:
        void runTest(string name, void (TDerivedClass::*fn)()) {
            cout << "Running test: " << name << endl;
            try {
                TDerivedClass* derived = (TDerivedClass*)this;
                (derived->*fn)();
                cout << "\\--Passed." << endl;
            } catch (exception& e) {
                cout << "\\--Failed: " << e.what() << endl;
            }
        }

    public:
        virtual ~TestSuiteBase() {}
};

#endif

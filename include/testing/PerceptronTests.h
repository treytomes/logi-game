#ifndef __PERCEPTRONTESTS_H__
#define __PERCEPTRONTESTS_H__

#include <exception>
using namespace std;

#include "ComponentFactory.h"
#include "Perceptron.h"
#include "testing/TestSuiteBase.h"

class PerceptronTests: public TestSuiteBase<PerceptronTests> {
    private:
        ComponentFactory* _factory;

    public:
        PerceptronTests();
        ~PerceptronTests();

        void runAll();
        void testPerceptronCanBeNOT();
        void testPerceptronCanBeAND();
        void testPerceptronCanBeOR();
        void testPerceptronCanBeNOR();
        void testPerceptronCanBeNAND();
};

#endif

#ifndef __CIRCUITTESTS_H__
#define __CIRCUITTESTS_H__

#include "Circuit.h"
#include "CircuitFactory.h"
#include "ConstantOutputSource.h"
#include "Perceptron.h"
#include "PerceptronFactory.h"
#include "testing/TestSuiteBase.h"

class CircuitTests: public TestSuiteBase<CircuitTests> {
    private:
        CircuitFactory* _factory;

    public:
        CircuitTests();
        ~CircuitTests();

        void runAll();
        void testCircuitXNOR();
        void testCircuitXOR();
};

#endif

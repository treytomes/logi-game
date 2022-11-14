#ifndef __CIRCUITTESTS_H__
#define __CIRCUITTESTS_H__

#include "Circuit.h"
#include "ComponentFactory.h"
#include "ConstantOutputSource.h"
#include "Perceptron.h"
#include "testing/TestSuiteBase.h"

class CircuitTests: public TestSuiteBase<CircuitTests> {
    private:
        ComponentFactory* _factory;

    public:
        CircuitTests();
        ~CircuitTests();

        void runAll();

        void testCircuitXNOR();
        void testCircuitXOR();
        void testSRLatch();
        void testClock();
        void testSRFlipFlop();
        void testDLatch();
        void testCounter();
};

#endif

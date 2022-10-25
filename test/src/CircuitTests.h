#ifndef __CIRCUITTESTS_H__
#define __CIRCUITTESTS_H__

#include "Circuit.h"
#include "ConstantOutputSource.h"
#include "Perceptron.h"
#include "PerceptronFactory.h"
#include "TestSuiteBase.h"

class CircuitTests: public TestSuiteBase<CircuitTests> {
    private:
        PerceptronFactory* _factory;

    public:
        CircuitTests() {
            _factory = new PerceptronFactory();
        }

        ~CircuitTests() {
            if (_factory != nullptr) {
                delete _factory;
                _factory = nullptr;
            }
        }

        void runAll() {
            runTest("Circuit ==> XNOR", &CircuitTests::testCircuitXNOR);
            runTest("Circuit ==> XOR", &CircuitTests::testCircuitXOR);
        }

        void testCircuitXNOR() {
            Circuit* circuit = new Circuit();

            ConstantOutputSource* input0 = circuit->addInput();
            ConstantOutputSource* input1 = circuit->addInput();

            Perceptron* and0 = circuit->addPerceptron(_factory->createAND());
            Perceptron* nor0 = circuit->addPerceptron(_factory->createNOR());
            Perceptron* or0 = circuit->addPerceptron(_factory->createOR(), true);

            circuit->connectFrom(input0)
                ->connectTo(and0, 0)
                ->connectTo(nor0, 0);
            circuit->connectFrom(input1)
                ->connectTo(and0, 1)
                ->connectTo(nor0, 1);
            circuit->connectFrom(and0)->connectTo(or0, 0);
            circuit->connectFrom(nor0)->connectTo(or0, 1);

            // There are 2 layers, so we need 1 update for the circuit to settle.

            input0->setOutput(0);
            input1->setOutput(0);
            circuit->step();
            assertEqual(1.0f, circuit->getOutput(0));

            input0->setOutput(0);
            input1->setOutput(1);
            circuit->step();
            assertEqual(0.0f, circuit->getOutput(0));

            input0->setOutput(1);
            input1->setOutput(0);
            circuit->step();
            assertEqual(0.0f, circuit->getOutput(0));

            input0->setOutput(1);
            input1->setOutput(1);
            circuit->step();
            assertEqual(1.0f, circuit->getOutput(0));

            delete circuit;
        }


        void testCircuitXOR() {
            Circuit* circuit = new Circuit();

            ConstantOutputSource* input0 = circuit->addInput();
            ConstantOutputSource* input1 = circuit->addInput();

            Perceptron* or0 = circuit->addPerceptron(_factory->createOR());
            Perceptron* nand0 = circuit->addPerceptron(_factory->createNAND());
            Perceptron* and0 = circuit->addPerceptron(_factory->createAND(), true);

            circuit->connectFrom(input0)
                ->connectTo(or0, 0)
                ->connectTo(nand0, 0);
            circuit->connectFrom(input1)
                ->connectTo(or0, 1)
                ->connectTo(nand0, 1);
            circuit->connectFrom(or0)->connectTo(and0, 0);
            circuit->connectFrom(nand0)->connectTo(and0, 1);

            // There are 2 layers, so we need 1 update for the circuit to settle.

            input0->setOutput(0);
            input1->setOutput(0);
            circuit->step();
            assertEqual(0.0f, circuit->getOutput(0));

            input0->setOutput(0);
            input1->setOutput(1);
            circuit->step();
            assertEqual(1.0f, circuit->getOutput(0));

            input0->setOutput(1);
            input1->setOutput(0);
            circuit->step();
            assertEqual(1.0f, circuit->getOutput(0));

            input0->setOutput(1);
            input1->setOutput(1);
            circuit->step();
            assertEqual(0.0f, circuit->getOutput(0));

            delete circuit;
        }
};

#endif

#include "testing/CircuitTests.h"
#include "CircuitFactory.h"

CircuitTests::CircuitTests() {
    _factory = new CircuitFactory();
}

CircuitTests::~CircuitTests() {
    if (_factory != nullptr) {
        delete _factory;
        _factory = nullptr;
    }
}

void CircuitTests::runAll() {
    runTest("Circuit ==> XNOR", &CircuitTests::testCircuitXNOR);
    runTest("Circuit ==> XOR", &CircuitTests::testCircuitXOR);
}

void CircuitTests::testCircuitXNOR() {
    Circuit* circuit =  _factory->createXNOR();

    // There are 2 layers, so we need 1 update for the circuit to settle.

    circuit->setInput(0, 0);
    circuit->setInput(1, 0);
    circuit->step();
    assertEqual(1.0f, circuit->getOutput(0));

    circuit->setInput(0, 0);
    circuit->setInput(1, 1);
    circuit->step();
    assertEqual(0.0f, circuit->getOutput(0));

    circuit->setInput(0, 1);
    circuit->setInput(1, 0);
    circuit->step();
    assertEqual(0.0f, circuit->getOutput(0));

    circuit->setInput(0, 1);
    circuit->setInput(1, 1);
    circuit->step();
    assertEqual(1.0f, circuit->getOutput(0));

    delete circuit;
}

void CircuitTests::testCircuitXOR() {
    Circuit* circuit = _factory->createXOR();

    // There are 2 layers, so we need 1 update for the circuit to settle.

    circuit->setInput(0, 0);
    circuit->setInput(1, 0);
    circuit->step();
    assertEqual(0.0f, circuit->getOutput(0));

    circuit->setInput(0, 0);
    circuit->setInput(1, 1);
    circuit->step();
    assertEqual(1.0f, circuit->getOutput(0));

    circuit->setInput(0, 1);
    circuit->setInput(1, 0);
    circuit->step();
    assertEqual(1.0f, circuit->getOutput(0));

    circuit->setInput(0, 1);
    circuit->setInput(1, 1);
    circuit->step();
    assertEqual(0.0f, circuit->getOutput(0));

    delete circuit;
}
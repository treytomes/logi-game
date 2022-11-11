#include "testing/CircuitTests.h"

CircuitTests::CircuitTests() {
    _factory = new ComponentFactory();
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
    runTest("Circuit ==> SR Latch", &CircuitTests::testSRLatch);
    runTest("Circuit ==> Clock", &CircuitTests::testClock);
    runTest("Circuit ==> SR Flip-Flop", &CircuitTests::testSRFlipFlop);
}

void CircuitTests::testCircuitXNOR() {
    Circuit* circuit = static_cast<Circuit*>(_factory->createXNOR());

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
    Circuit* circuit = static_cast<Circuit*>(_factory->createXOR());

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

void CircuitTests::testClock() {
    INetworkable* circuit = _factory->createClock();

    for (int n = 0; n < 100; n++) {
        assertEqual(1.0f, circuit->getOutput(0));
        circuit->step();
        assertEqual(0.0f, circuit->getOutput(0));
        circuit->step();
    }

    delete circuit;
}

void CircuitTests::testSRLatch() {
    // The recursion in the circuit causes it to require 2 steps for the state to settle.

    // RESET is input 0.
    // SET is input 1.
    // Q is output 1.
    // Q! is output 0.

    INetworkable* circuit = _factory->createSRLatch();

    float q = 0;
    float qNot = 0;

    // Can we set the output?
    circuit->setInput(0, 0);
    circuit->setInput(1, 1);
    circuit->step();
    circuit->step();
    q = circuit->getOutput(1);
    qNot = circuit->getOutput(0);
    assertEqual(1.0f, q);
    assertEqual(0.0f, qNot);

    // Is the set state being saved?
    circuit->setInput(0, 0);
    circuit->setInput(1, 0);
    circuit->step();
    circuit->step();
    q = circuit->getOutput(1);
    qNot = circuit->getOutput(0);
    assertEqual(1.0f, q);
    assertEqual(0.0f, qNot);

    // Can we reset the state?
    circuit->setInput(0, 1);
    circuit->setInput(1, 0);
    circuit->step();
    circuit->step();
    q = circuit->getOutput(1);
    qNot = circuit->getOutput(0);
    assertEqual(0.0f, q);
    assertEqual(1.0f, qNot);

    // Is the reset state being saved?
    circuit->setInput(0, 0);
    circuit->setInput(1, 0);
    circuit->step();
    circuit->step();
    q = circuit->getOutput(1);
    qNot = circuit->getOutput(0);
    assertEqual(0.0f, q);
    assertEqual(1.0f, qNot);

    delete circuit;
}

void CircuitTests::testSRFlipFlop() {
    INetworkable* circuit = _factory->createSRFlipFlop();

    float q1;
    float qNot1;

    // Turn on the enable line.
    circuit->setInput(1, 1);

    // Can we set the output?
    circuit->setInput(0, 0);
    circuit->setInput(2, 1);
    circuit->step();
    circuit->step();
    circuit->step();
    q1 = circuit->getOutput(1);
    qNot1 = circuit->getOutput(0);
    assertEqual(1.0f, q1);
    assertEqual(0.0f, qNot1);

    // Is the set state being saved?
    circuit->setInput(0, 0);
    circuit->setInput(2, 0);
    circuit->step();
    circuit->step();
    circuit->step();
    q1 = circuit->getOutput(1);
    qNot1 = circuit->getOutput(0);
    assertEqual(1.0f, q1);
    assertEqual(0.0f, qNot1);

    // Can we reset the state?
    circuit->setInput(0, 1);
    circuit->setInput(2, 0);
    circuit->step();
    circuit->step();
    circuit->step();
    q1 = circuit->getOutput(1);
    qNot1 = circuit->getOutput(0);
    assertEqual(0.0f, q1);
    assertEqual(1.0f, qNot1);

    // Is the reset state being saved?
    circuit->setInput(0, 0);
    circuit->setInput(2, 0);
    circuit->step();
    circuit->step();
    circuit->step();
    q1 = circuit->getOutput(1);
    qNot1 = circuit->getOutput(0);
    assertEqual(0.0f, q1);
    assertEqual(1.0f, qNot1);

    // Turn off the enable line.
    circuit->setInput(1, 0);

    // Store the initial state to test against.
    float expectedQ0 = circuit->getOutput(1);
    float expectedQNot0 = circuit->getOutput(0);

    // Can we set the output?
    circuit->setInput(0, 0);
    circuit->setInput(2, 1);
    circuit->step();
    circuit->step();
    circuit->step();
    q1 = circuit->getOutput(1);
    qNot1 = circuit->getOutput(0);
    assertEqual(expectedQ0, q1);
    assertEqual(expectedQNot0, qNot1);

    // Is the set state being saved?
    circuit->setInput(0, 0);
    circuit->setInput(2, 0);
    circuit->step();
    circuit->step();
    circuit->step();
    q1 = circuit->getOutput(1);
    qNot1 = circuit->getOutput(0);
    assertEqual(expectedQ0, q1);
    assertEqual(expectedQNot0, qNot1);

    // Can we reset the state?
    circuit->setInput(0, 1);
    circuit->setInput(2, 0);
    circuit->step();
    circuit->step();
    circuit->step();
    q1 = circuit->getOutput(1);
    qNot1 = circuit->getOutput(0);
    assertEqual(expectedQ0, q1);
    assertEqual(expectedQNot0, qNot1);

    // Is the reset state being saved?
    circuit->setInput(0, 0);
    circuit->setInput(2, 0);
    circuit->step();
    circuit->step();
    circuit->step();
    q1 = circuit->getOutput(1);
    qNot1 = circuit->getOutput(0);
    assertEqual(expectedQ0, q1);
    assertEqual(expectedQNot0, qNot1);

    delete circuit;
}
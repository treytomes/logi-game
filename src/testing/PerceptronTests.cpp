#include "testing/PerceptronTests.h"

PerceptronTests::PerceptronTests() {
    _factory = new ComponentFactory();
}

PerceptronTests::~PerceptronTests() {
    if (_factory != nullptr) {
        delete _factory;
        _factory = nullptr;
    }
}

void PerceptronTests::runAll() {
    runTest("Perceptron ==> NOT", &PerceptronTests::testPerceptronCanBeNOT);
    runTest("Perceptron ==> AND", &PerceptronTests::testPerceptronCanBeAND);
    runTest("Perceptron ==> OR", &PerceptronTests::testPerceptronCanBeOR);
    runTest("Perceptron ==> NOR", &PerceptronTests::testPerceptronCanBeNOR);
    runTest("Perceptron ==> NAND", &PerceptronTests::testPerceptronCanBeNAND);
    runTest("Perceptron ==> Diode", &PerceptronTests::testPerceptronCanBeDiode);
}

void PerceptronTests::testPerceptronCanBeNOT() {
    INetworkable* p0 = _factory->createNOT();
    try {
        p0->setInput(0, 0);
        assertEqual(1.0f, p0->getOutput());

        p0->setInput(0, 1);
        assertEqual(0.0f, p0->getOutput());
    } catch (exception&) {
        delete p0;
        throw;
    }

    delete p0;
}

void PerceptronTests::testPerceptronCanBeAND() {
    INetworkable* p0 = _factory->createAND();
    try {
        p0->setInput(0, 0);
        p0->setInput(1, 0);
        assertEqual(0.0f, p0->getOutput());

        p0->setInput(0, 0);
        p0->setInput(1, 1);
        assertEqual(0.0f, p0->getOutput());

        p0->setInput(0, 1);
        p0->setInput(1, 0);
        assertEqual(0.0f, p0->getOutput());

        p0->setInput(0, 1);
        p0->setInput(1, 1);
        assertEqual(1.0f, p0->getOutput());
    } catch (exception&) {
        delete p0;
        throw;
    }

    delete p0;
}

void PerceptronTests::testPerceptronCanBeOR() {
    INetworkable* p0 = _factory->createOR();
    try {
        p0->setInput(0, 0);
        p0->setInput(1, 0);
        assertEqual(0.0f, p0->getOutput());

        p0->setInput(0, 0);
        p0->setInput(1, 1);
        assertEqual(1.0f, p0->getOutput());

        p0->setInput(0, 1);
        p0->setInput(1, 0);
        assertEqual(1.0f, p0->getOutput());

        p0->setInput(0, 1);
        p0->setInput(1, 1);
        assertEqual(1.0f, p0->getOutput());
    } catch (exception&) {
        delete p0;
        throw;
    }

    delete p0;
}

void PerceptronTests::testPerceptronCanBeNOR() {
    INetworkable* p0 = _factory->createNOR();
    try {
        p0->setInput(0, 0);
        p0->setInput(1, 0);
        assertEqual(1.0f, p0->getOutput());

        p0->setInput(0, 0);
        p0->setInput(1, 1);
        assertEqual(0.0f, p0->getOutput());

        p0->setInput(0, 1);
        p0->setInput(1, 0);
        assertEqual(0.0f, p0->getOutput());

        p0->setInput(0, 1);
        p0->setInput(1, 1);
        assertEqual(0.0f, p0->getOutput());
    } catch (exception&) {
        delete p0;
        throw;
    }

    delete p0;
}

void PerceptronTests::testPerceptronCanBeNAND() {
    INetworkable* p0 = _factory->createNAND();
    try {
        p0->setInput(0, 0);
        p0->setInput(1, 0);
        assertEqual(1.0f, p0->getOutput());

        p0->setInput(0, 0);
        p0->setInput(1, 1);
        assertEqual(1.0f, p0->getOutput());

        p0->setInput(0, 1);
        p0->setInput(1, 0);
        assertEqual(1.0f, p0->getOutput());

        p0->setInput(0, 1);
        p0->setInput(1, 1);
        assertEqual(0.0f, p0->getOutput());

        delete p0;
    } catch (exception&) {
        delete p0;
        throw;
    }
}

void PerceptronTests::testPerceptronCanBeDiode() {
    INetworkable* p0 = _factory->createDiode();
    try {
        p0->setInput(0, 0);
        float output = p0->getOutput();
        assertEqual(0.0f, output);

        p0->setInput(0, 1);
        output = p0->getOutput();
        assertEqual(1.0f, output);

        delete p0;
    }
    catch (exception&) {
        delete p0;
        throw;
    }
}
#include "Circuit.h"

Circuit::Circuit() {
}

Circuit::~Circuit() {
    for (auto it = _inputs.begin(); it != _inputs.end(); it++) {
        delete *it;
    }
    _inputs.clear();

    for (auto it = _perceptrons.begin(); it != _perceptrons.end(); it++) {
        delete *it;
    }
    _perceptrons.clear();

    for (auto it = _wires.begin(); it != _wires.end(); it++) {
        delete *it;
    }
    _wires.clear();
}

ConstantOutputSource* Circuit::addInput(float value) {
    ConstantOutputSource* input = new ConstantOutputSource(value);
    _inputs.push_back(input);
    return input;
}

Perceptron* Circuit::addPerceptron(Perceptron* perceptron, bool isOutput) {
    _perceptrons.push_back(perceptron);
    if (isOutput) {
        _outputs.push_back(perceptron);
    }
    return perceptron;
}

void Circuit::setInput(int inputNumber, float value) {
    OutOfRangeException(inputNumber, 0, (int)_inputs.size()).assert();
    _inputs[inputNumber]->setOutput(value);
}

float Circuit::getOutput(int outputNumber) {
    OutOfRangeException(outputNumber, 0, (int)_outputs.size()).assert();
    return _outputs[outputNumber]->getOutput();
}

PerceptronWire* Circuit::connectFrom(IHasOutput* source) {
    PerceptronWire* wire = new PerceptronWire(source);
    _wires.push_back(wire);
    return wire;
}

void Circuit::step() {
    for (auto it = _wires.begin(); it != _wires.end(); it++) {
        (*it)->step();
    }
}

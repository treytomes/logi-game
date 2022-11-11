#include "Circuit.h"

Circuit::Circuit() {
}

Circuit::~Circuit() {
    for (auto it = _inputs.begin(); it != _inputs.end(); it++) {
        delete *it;
    }
    _inputs.clear();

    for (auto it = _components.begin(); it != _components.end(); it++) {
        delete *it;
    }
    _components.clear();

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

INetworkable* Circuit::addComponent(INetworkable* component, bool isOutput) {
    _components.push_back(component);
    if (isOutput) {
        _outputs.push_back(component);
    }
    return component;
}

void Circuit::setInput(int inputNumber, float value) {
    OutOfRangeException(inputNumber, 0, (int)_inputs.size()).assert();
    _inputs[inputNumber]->setInput(0, value);
}

float Circuit::getOutput(int outputNumber) {
    OutOfRangeException(outputNumber, 0, (int)_outputs.size()).assert();
    return _outputs[outputNumber]->getOutput();
}

Wire* Circuit::connectFrom(INetworkable* source, int outputNumber) {
    Wire* wire = new Wire(source, outputNumber);
    _wires.push_back(wire);
    return wire;
}

void Circuit::step() {
    for (auto it = _wires.begin(); it != _wires.end(); it++) {
        (*it)->step();
    }
    for (auto it = _components.begin(); it != _components.end(); it++) {
        (*it)->step();
    }
}

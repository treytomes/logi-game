#include "Wire.h"

Wire::Wire(INetworkable* source, int outputNumber)
    : _source(new WireConnection(source, outputNumber)) {
}

Wire::~Wire() {
    for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
        delete* iter;
    }
    _targets.clear();

    delete _source;
    _source = nullptr;
}

bool Wire::isConnected(INetworkable* target) {
    for (auto it = _targets.begin(); it != _targets.end(); it++) {
        if ((*it)->getTarget() == target) {
            return true;
        }
    }
    return false;
}

Wire* Wire::connectTo(INetworkable* target, int inputNumber) {
    if (target == nullptr) {
        throw ArgumentNullException("target");
    }
    if (!isConnected(target)) {
        _targets.push_back(new WireConnection(target, inputNumber));
    }
    return this;
}

void Wire::disconnect(INetworkable* target) {
    for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
        WireConnection* conn = *iter;
        if (conn->getTarget() == target) {
            _targets.erase(iter);
            break;
        }
    }
}

void Wire::step() {
    WireConnection* outputConnection = getSource();
    INetworkable* source = outputConnection->getTarget();
    float value = source->getOutput(outputConnection->getPortNumber());

    for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
        WireConnection* conn = *iter;
        conn->getTarget()->setInput(conn->getPortNumber(), value);
    }
}

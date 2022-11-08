#ifndef __PERCEPTRONWIRE_H__
#define __PERCEPTRONWIRE_H__

#include <vector>
using namespace std;

#include "INetworkable.h"
#include "Perceptron.h"
#include "PerceptronWireConnection.h"

class PerceptronWire {
    private:
        INetworkable* _source;
        vector<PerceptronWireConnection*> _targets;

    public:
        PerceptronWire(INetworkable* source)
            : _source(source) {
            if (source == nullptr) {
                throw ArgumentNullException("source");
            }
        }

        ~PerceptronWire() {
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                delete *iter;
            }
            _targets.clear();
        }

        inline INetworkable* getSource() { return _source; }

        inline bool isConnected(Perceptron* target) {
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                PerceptronWireConnection* conn = *iter;
                if (conn->getTarget() == target) {
                    return true;
                }
            }
            return false;
        }

        PerceptronWire* connectTo(Perceptron* target, int inputNumber) {
            if (target == nullptr) {
                throw ArgumentNullException("target");
            }
            if (!isConnected(target)) {
                _targets.push_back(new PerceptronWireConnection(target, inputNumber));
            }
            return this;
        }

        void disconnect(Perceptron* target) {
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                PerceptronWireConnection* conn = *iter;
                if (conn->getTarget() == target) {
                    _targets.erase(iter);
                    break;
                }
            }
        }

        void step() {
            float value = getSource()->getOutput();
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                PerceptronWireConnection* conn = *iter;
                conn->getTarget()->setInput(conn->getInputNumber(), value);
            }
        }
};

#endif

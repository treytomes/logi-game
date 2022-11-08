#ifndef __PERCEPTRONWIRE_H__
#define __PERCEPTRONWIRE_H__

#include <vector>
using namespace std;

#include "IHasOutput.h"
#include "Perceptron.h"
#include "WireConnection.h"

class Wire {
    private:
        IHasOutput* _source;
        vector<WireConnection*> _targets;

    public:
        Wire(IHasOutput* source)
            : _source(source) {
            if (source == nullptr) {
                throw ArgumentNullException("source");
            }
        }

        ~Wire() {
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                delete *iter;
            }
            _targets.clear();
        }

        inline IHasOutput* getSource() { return _source; }

        inline bool isConnected(IHasInput* target) {
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                WireConnection* conn = *iter;
                if (conn->getTarget() == target) {
                    return true;
                }
            }
            return false;
        }

        Wire* connectTo(IHasInput* target, int inputNumber) {
            if (target == nullptr) {
                throw ArgumentNullException("target");
            }
            if (!isConnected(target)) {
                _targets.push_back(new WireConnection(target, inputNumber));
            }
            return this;
        }

        void disconnect(IHasInput* target) {
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                WireConnection* conn = *iter;
                if (conn->getTarget() == target) {
                    _targets.erase(iter);
                    break;
                }
            }
        }

        void step() {
            float value = getSource()->getOutput();
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                WireConnection* conn = *iter;
                conn->getTarget()->setInput(conn->getInputNumber(), value);
            }
        }
};

#endif

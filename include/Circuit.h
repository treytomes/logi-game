#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include <vector>
using namespace std;

#include "ConstantOutputSource.h"
#include "Perceptron.h"
#include "PerceptronWire.h"

class Circuit {
    private:
        vector<ConstantOutputSource*> _inputs;
        vector<Perceptron*> _perceptrons;
        vector<PerceptronWire*> _wires;
        vector<Perceptron*> _outputs;

    public:
        Circuit() {}

        ~Circuit() {
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

        ConstantOutputSource* addInput(float value = 0) {
            ConstantOutputSource* input = new ConstantOutputSource(value);
            _inputs.push_back(input);
            return input;
        }

        Perceptron* addPerceptron(Perceptron* perceptron, bool isOutput = false) {
            _perceptrons.push_back(perceptron);
            if (isOutput) {
                _outputs.push_back(perceptron);
            }
            return perceptron;
        }

        void setInput(int inputNumber, float value) {
            if ((inputNumber < 0) || (inputNumber >= (int)_inputs.size())) {
                throw OutOfRangeException(inputNumber, 0, (int)_inputs.size());
            }
            _inputs[inputNumber]->setOutput(value);
        }

        float getOutput(int outputNumber) {
            if ((outputNumber < 0) || (outputNumber >= (int)_outputs.size())) {
                throw OutOfRangeException(outputNumber, 0, (int)_outputs.size());
            }
            return _outputs[outputNumber]->getOutput();
        }

        PerceptronWire* connectFrom(IHasOutput* source) {
            PerceptronWire* wire = new PerceptronWire(source);
            _wires.push_back(wire);
            return wire;
        }

        void step() {
            for (auto it = _wires.begin(); it != _wires.end(); it++) {
                (*it)->step();
            }
        }
};

#endif

#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__

#include "INetworkable.h"
#include "OutOfRangeException.h"

class Perceptron: public INetworkable {
    private:
        int _numInputs;
        float _bias;
        float* _weights;
        float* _inputs;

    public:
        Perceptron(int numInputs)
            : _numInputs(numInputs) {
            _weights = new float[_numInputs];
            _inputs = new float[_numInputs];
            clear();
        }

        ~Perceptron() {
            if (_weights != nullptr) {
                delete[] _weights;
                _weights = nullptr;
            }
            if (_inputs != nullptr) {
                delete[] _inputs;
                _inputs = nullptr;
            }
        }

        inline void clear() {
            _bias = 0;
            for (int n = 0; n < _numInputs; n++) {
                setWeight(n, 0);
                setInput(n, 0);
            }
        }

        inline void setBias(float value) {
            _bias = value;
        }

        inline float getBias() {
            return _bias;
        }

        inline void setWeight(int n, float value) {
            if ((n < 0) || (n >= getNumInputs())) {
                throw OutOfRangeException(n, 0, getNumInputs());
            }
            _weights[n] = value;
        }

        inline float getWeight(int n) {
            if ((n < 0) || (n >= getNumInputs())) {
                throw OutOfRangeException(n, 0, getNumInputs());
            }
            return _weights[n];
        }

        inline void setInput(int inputNumber, float value) {
            if ((inputNumber < 0) || (inputNumber >= getNumInputs())) {
                throw OutOfRangeException(inputNumber, 0, getNumInputs());
            }
            _inputs[inputNumber] = value;
        }

        inline int getNumInputs() {
            return _numInputs;
        }

        inline float getInput(int n) {
            if ((n < 0) || (n >= getNumInputs())) {
                throw OutOfRangeException(n, 0, getNumInputs());
            }
            return _inputs[n];
        }

        inline int getNumOutputs() { return 1; }

        inline float getOutput(int outputNumber = 0) {
            OutOfRangeException(outputNumber, 0, 1).assert();
            float output = 0;
            for (int n = 0; n < getNumInputs(); n++) {
                output += getWeight(n) * getInput(n);
            }
            output += getBias();
            return (output > 0.0f) ? 1.0f : 0.0f;
        }

        // Nothing actually to do, but it needs to be here to exist in a network.
        inline void step() {}
};

#endif

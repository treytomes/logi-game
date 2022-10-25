#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__

#include "IHasOutput.h"
#include "OutOfRangeException.h"


class Perceptron: public IHasOutput {
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

        inline int getNumInputs() {
            return _numInputs;
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

        inline void setInput(int n, float value) {
            if ((n < 0) || (n >= getNumInputs())) {
                throw OutOfRangeException(n, 0, getNumInputs());
            }
            _inputs[n] = value;
        }

        inline float getInput(int n) {
            if ((n < 0) || (n >= getNumInputs())) {
                throw OutOfRangeException(n, 0, getNumInputs());
            }
            return _inputs[n];
        }

        inline float getOutput() {
            float output = 0;
            for (int n = 0; n < getNumInputs(); n++) {
                output += getWeight(n) * getInput(n);
            }
            output += getBias();
            return (output > 0) ? 1 : 0;
        }
};

#endif

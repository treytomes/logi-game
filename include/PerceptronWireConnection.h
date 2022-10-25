#ifndef __PERCEPTRONWIRECONNECTION_H__
#define __PERCEPTRONWIRECONNECTION_H__

#include "ArgumentNullException.h"
#include "Perceptron.h"

class PerceptronWireConnection {
    private:
        Perceptron* _target;
        int _inputNumber;

    public:
        PerceptronWireConnection(Perceptron* target, int inputNumber)
            : _target(target), _inputNumber(inputNumber) {
            if (target == nullptr) {
                throw ArgumentNullException("target");
            }
        }

        inline Perceptron* getTarget() { return _target; }
        inline int getInputNumber() { return _inputNumber; }
};

#endif

#ifndef __PERCEPTRONWIRECONNECTION_H__
#define __PERCEPTRONWIRECONNECTION_H__

#include "ArgumentNullException.h"
#include "IHasInput.h"
#include "Perceptron.h"

class WireConnection {
    private:
        IHasInput* _target;
        int _inputNumber;

    public:
        WireConnection(IHasInput* target, int inputNumber)
            : _target(target), _inputNumber(inputNumber) {
            if (target == nullptr) {
                throw ArgumentNullException("target");
            }
        }

        inline IHasInput* getTarget() { return _target; }
        inline int getInputNumber() { return _inputNumber; }
};

#endif

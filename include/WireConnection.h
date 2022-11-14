#ifndef __PERCEPTRONWIRECONNECTION_H__
#define __PERCEPTRONWIRECONNECTION_H__

#include "ArgumentNullException.h"
#include "INetworkable.h"
#include "Perceptron.h"

class WireConnection {
    private:
        INetworkable* _target;
        int _portNumber;

    public:
        WireConnection(INetworkable* target, int portNumber)
            : _target(target), _portNumber(portNumber) {
            if (target == nullptr) {
                throw ArgumentNullException("target");
            }
        }

        inline INetworkable* getTarget() { return _target; }
        inline int getPortNumber() { return _portNumber; }
};

#endif

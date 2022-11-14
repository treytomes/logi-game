#ifndef __PERCEPTRONWIRE_H__
#define __PERCEPTRONWIRE_H__

#include <vector>
using namespace std;

#include "Perceptron.h"
#include "WireConnection.h"

class Wire {
    private:
        WireConnection* _source;
        vector<WireConnection*> _targets;

    public:
        Wire(INetworkable* source, int outputNumber);
        ~Wire();

        inline WireConnection* getSource() { return _source; }

        bool isConnected(INetworkable* target);
        Wire* connectTo(INetworkable* target, int inputNumber);
        void disconnect(INetworkable* target);
        void step();
};

#endif

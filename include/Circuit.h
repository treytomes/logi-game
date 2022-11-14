#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include <vector>
using namespace std;

#include "ConstantOutputSource.h"
#include "INetworkable.h"
#include "Perceptron.h"
#include "Wire.h"

class Circuit : public INetworkable {
    private:
        vector<ConstantOutputSource*> _inputs;
        vector<INetworkable*> _components;
        vector<Wire*> _wires;
        vector<INetworkable*> _outputs;

    public:
        Circuit();
        ~Circuit();

        ConstantOutputSource* addInput(float value = 0);
        INetworkable* addComponent(INetworkable* component, bool isOutput = false);

        inline int getNumInputs() { return (int)_inputs.size(); }
        void setInput(int inputNumber, float value);
        inline int getNumOutputs() { return (int)_outputs.size(); }
        float getOutput(int outputNumber);
        Wire* connectFrom(INetworkable* source, int outputNumber);
        void step();
};

#endif

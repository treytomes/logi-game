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
        Circuit();
        ~Circuit();

        ConstantOutputSource* addInput(float value = 0);
        Perceptron* addPerceptron(Perceptron* perceptron, bool isOutput = false);
        void setInput(int inputNumber, float value);
        float getOutput(int outputNumber);
        PerceptronWire* connectFrom(IHasOutput* source);
        void step();
};

#endif

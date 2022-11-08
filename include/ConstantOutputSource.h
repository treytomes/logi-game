#ifndef __CONSTANTOUTPUTSOURCE_H__
#define __CONSTANTOUTPUTSOURCE_H__

#include "INetworkable.h"
#include "OutOfRangeException.h"

class ConstantOutputSource: public INetworkable {
    private:
        float _output;

    public:
        ConstantOutputSource(float output = 0) : _output(output) {}

        void setInput(int inputNumber, float value) {
            OutOfRangeException(inputNumber, 0, 1).assert();
            _output = value;
        }

        inline float getOutput(int outputNumber = 0) {
            OutOfRangeException(outputNumber, 0, 1).assert();
            return _output;
        }

        inline void step() {}
};

#endif

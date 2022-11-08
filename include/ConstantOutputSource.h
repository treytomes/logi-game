#ifndef __CONSTANTOUTPUTSOURCE_H__
#define __CONSTANTOUTPUTSOURCE_H__

#include "INetworkable.h"

class ConstantOutputSource: public INetworkable {
    private:
        float _output;

    public:
        ConstantOutputSource(float output = 0) : _output(output) {}
        inline float getOutput() { return _output; }
        inline void setOutput(float output) { _output = output; }
};

#endif

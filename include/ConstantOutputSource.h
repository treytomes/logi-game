#ifndef __CONSTANTOUTPUTSOURCE_H__
#define __CONSTANTOUTPUTSOURCE_H__

#include "IHasOutput.h"

class ConstantOutputSource: public IHasOutput {
    private:
        float _output;

    public:
        ConstantOutputSource(float output = 0) : _output(output) {}
        inline float getOutput() { return _output; }
        inline void setOutput(float output) { _output = output; }
};

#endif

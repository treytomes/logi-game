#ifndef __IHASOUTPUT_H__
#define __IHASOUTPUT_H__

class IHasOutput {
    public:
        virtual ~IHasOutput() {}
        virtual float getOutput(int outputNumber = 0) = 0;
};

#endif

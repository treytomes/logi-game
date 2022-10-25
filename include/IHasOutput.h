#ifndef __IHASOUTPUT_H__
#define __IHASOUTPUT_H__

class IHasOutput {
    public:
        virtual ~IHasOutput() {}
        virtual float getOutput() = 0;
};

#endif

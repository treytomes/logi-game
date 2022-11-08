#ifndef __IHASOUTPUT_H__
#define __IHASOUTPUT_H__

class INetworkable {
    public:
        virtual ~INetworkable() {}
        virtual float getOutput() = 0;
};

#endif

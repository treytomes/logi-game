#ifndef __INETWORKABLE_H__
#define __INETWORKABLE_H__

class INetworkable {
	public:
		virtual void setInput(int inputNumber, float value) = 0;
		virtual float getOutput(int outputNumber = 0) = 0;
		virtual void step() = 0;
};

#endif

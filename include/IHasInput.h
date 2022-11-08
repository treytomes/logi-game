#ifndef __ICIRCUIT_H__
#define __ICIRCUIT_H__

class IHasInput {
public:
	virtual void setInput(int inputNumber, float value) = 0;
};

#endif

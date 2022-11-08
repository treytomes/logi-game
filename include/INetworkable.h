#ifndef __INETWORKABLE_H__
#define __INETWORKABLE_H__

#include "IHasInput.h"
#include "IHasOutput.h"

class INetworkable : public IHasInput, public IHasOutput {
	public:
		virtual void step() = 0;
};

#endif

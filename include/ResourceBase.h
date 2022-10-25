#ifndef __RESOURCEBASE_H__
#define __RESOURCEBASE_H__

#include "Resource.h"

template <typename TValue>
class ResourceBase: public Resource {
	private:
		TValue* _value;

	protected:
		inline void setValue(TValue* value) { _value = value; }

	public:
		ResourceBase(string key, string path) : Resource(key, path) {}

		inline TValue* getValue() { return _value; }

		virtual void load() = 0;
		virtual void unload() = 0;
};

#endif

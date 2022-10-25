#ifndef __FONTRESOURCE_H__
#define __FONTRESOURCE_H__

#include "ResourceBase.h"

class FontResource: public ResourceBase<TTF_Font> {
	public:
		FontResource(string key, string path) : ResourceBase(key, path) {}

		void load();
		void unload();
};

#endif

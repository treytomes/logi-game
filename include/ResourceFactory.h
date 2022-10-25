#ifndef __RESOURCEFACTORY_H__
#define __RESOURCEFACTORY_H__

#include <map>
#include "Resource.h"
using namespace std;

class ResourceFactory {
	private:
		static ResourceFactory* _instance;
		map<string, Resource*> _resources;
		ResourceFactory();

	public:
		static ResourceFactory* get();
		static void shutdown();

		~ResourceFactory();
		
		template <typename TResource>
		inline TResource* get(const char* key) {
			return dynamic_cast<TResource*>(_resources[key]);
		}

		template <typename TResource>
		TResource* load(const char* key, const char* path) {
			TResource* resource = new TResource(key, path);
			resource->load();
			_resources[key] = resource;
			return resource;
		}
};

#endif

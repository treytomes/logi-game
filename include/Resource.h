#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>
using namespace std;

class Resource {
	private:
		string _key;
		string _path;

	public:
		Resource(string key, string path) : _key(key), _path(path) {}
		virtual ~Resource() {}

		inline string getKey() { return _key; }
		inline string getPath() { return _path; }
		
		virtual void load() = 0;
		virtual void unload() = 0;
};

#endif

#include "ResourceFactory.h"

ResourceFactory* ResourceFactory::_instance = nullptr;

ResourceFactory* ResourceFactory::get() {
	if (_instance == nullptr) {
		_instance = new ResourceFactory();
	}
	return _instance;
}

void ResourceFactory::shutdown() {
	if (_instance != nullptr) {
		delete _instance;
		_instance = nullptr;
	}
}

ResourceFactory::ResourceFactory() {
}

ResourceFactory::~ResourceFactory() {
	for (const auto& [key, value] : _resources) {
		value->unload();
		delete value;
	}
	_resources.clear();
}

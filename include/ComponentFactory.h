#ifndef __COMPONENTFACTORY_H__
#define __COMPONENTFACTORY_H__

#include "INetworkable.h"

class ComponentFactory {
    public:
        INetworkable* createNOT();
        INetworkable* createAND();
        INetworkable* createOR();
        INetworkable* createNOR();
        INetworkable* createNAND();
        INetworkable* createXNOR();
        INetworkable* createXOR();
};

#endif
#ifndef __COMPONENTFACTORY_H__
#define __COMPONENTFACTORY_H__

#include <string>
using namespace std;

#include "INetworkable.h"

class ComponentFactory {
    public:
        INetworkable* loadFile(string path);

        INetworkable* createNOT();
        INetworkable* createAND();
        INetworkable* createOR();
        INetworkable* createNOR();
        INetworkable* createNAND();
        INetworkable* createXNOR();
        INetworkable* createXOR();

        /**
         * The recursion in the circuit causes it to require 2 steps for the state to settle.
         *
         * RESET is input 0.
         * SET is input 1.
         * Q is output 0.
         * Q! is output 1.
         */
        INetworkable* createSRLatch();
};

#endif
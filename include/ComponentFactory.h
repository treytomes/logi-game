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
         * Copy input to output.
         */
        INetworkable* createDiode();

        /**
         * A simple clock that flips it's state on each step.
         */
        INetworkable* createClock();

        /**
         * The recursion in the circuit causes it to require 2 steps for the state to settle.
         *
         * RESET is input 0.
         * SET is input 1.
         * Q is output 1.
         * Q! is output 0.
         */
        INetworkable* createSRLatch();

        /**
         * The flip-flop has one extra layer added for the enable line, so that's one more step for the state to settle.
         *
         * RESET is input 0.
         * ENABLE is input 1.
         * SET is input 2.
         * Q is output 1.
         * Q! is output 0.
         */
        INetworkable* createSRFlipFlop();
};

#endif
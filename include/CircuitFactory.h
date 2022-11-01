#ifndef __CIRCUITFACTORY_H__
#define __CIRCUITFACTORY_H__

#include "Circuit.h"
#include "Perceptron.h"
#include "PerceptronFactory.h"

class CircuitFactory {
    private:
        PerceptronFactory* _factory;

    public:
        Circuit* createXNOR();
        Circuit* createXOR();
};

#endif

#ifndef __PERCEPTRONFACTORY_H__
#define __PERCEPTRONFACTORY_H__

#include "Perceptron.h"

class PerceptronFactory {
    public:
        Perceptron* createNOT() {
            Perceptron* p0 = new Perceptron(1);
            p0->setBias(1);
            p0->setWeight(0, -1);
            return p0;
        }

        Perceptron* createAND() {
            Perceptron* p0 = new Perceptron(2);
            p0->setBias(-1);
            p0->setWeight(0, 1);
            p0->setWeight(1, 1);
            return p0;
        }

        Perceptron* createOR() {
            Perceptron* p0 = new Perceptron(2);
            p0->setBias(-1);
            p0->setWeight(0, 2);
            p0->setWeight(1, 2);
            return p0;
        }

        Perceptron* createNOR() {
            Perceptron* p0 = new Perceptron(2);
            p0->setBias(1);
            p0->setWeight(0, -1);
            p0->setWeight(1, -1);
            return p0;
        }

        Perceptron* createNAND() {
            Perceptron* p0 = new Perceptron(2);
            p0->setBias(2);
            p0->setWeight(0, -1);
            p0->setWeight(1, -1);
            return p0;
        }
};

#endif

#include "ComponentFactory.h"

#include "Circuit.h"
#include "Perceptron.h"

INetworkable* ComponentFactory::createNOT() {
    Perceptron* p0 = new Perceptron(1);
    p0->setBias(1);
    p0->setWeight(0, -1);
    return p0;
}

INetworkable* ComponentFactory::createAND() {
    Perceptron* p0 = new Perceptron(2);
    p0->setBias(-1);
    p0->setWeight(0, 1);
    p0->setWeight(1, 1);
    return p0;
}

INetworkable* ComponentFactory::createOR() {
    Perceptron* p0 = new Perceptron(2);
    p0->setBias(-1);
    p0->setWeight(0, 2);
    p0->setWeight(1, 2);
    return p0;
}

INetworkable* ComponentFactory::createNOR() {
    Perceptron* p0 = new Perceptron(2);
    p0->setBias(1);
    p0->setWeight(0, -1);
    p0->setWeight(1, -1);
    return p0;
}

INetworkable* ComponentFactory::createNAND() {
    Perceptron* p0 = new Perceptron(2);
    p0->setBias(2);
    p0->setWeight(0, -1);
    p0->setWeight(1, -1);
    return p0;
}

INetworkable* ComponentFactory::createXNOR() {
    Circuit* circuit = new Circuit();

    INetworkable* input0 = circuit->addInput();
    INetworkable* input1 = circuit->addInput();

    INetworkable* and0 = circuit->addComponent(createAND());
    INetworkable* nor0 = circuit->addComponent(createNOR());
    INetworkable* or0 = circuit->addComponent(createOR(), true);

    circuit->connectFrom(input0)
        ->connectTo(and0, 0)
        ->connectTo(nor0, 0);
    circuit->connectFrom(input1)
        ->connectTo(and0, 1)
        ->connectTo(nor0, 1);
    circuit->connectFrom(and0)->connectTo(or0, 0);
    circuit->connectFrom(nor0)->connectTo(or0, 1);

    return circuit;
}

INetworkable* ComponentFactory::createXOR() {
    Circuit* circuit = new Circuit();

    INetworkable* input0 = circuit->addInput();
    INetworkable* input1 = circuit->addInput();

    INetworkable* or0 = circuit->addComponent(createOR());
    INetworkable* nand0 = circuit->addComponent(createNAND());
    INetworkable* and0 = circuit->addComponent(createAND(), true);

    circuit->connectFrom(input0)
        ->connectTo(or0, 0)
        ->connectTo(nand0, 0);
    circuit->connectFrom(input1)
        ->connectTo(or0, 1)
        ->connectTo(nand0, 1);
    circuit->connectFrom(or0)->connectTo(and0, 0);
    circuit->connectFrom(nand0)->connectTo(and0, 1);

    return circuit;
}

INetworkable* ComponentFactory::createSRLatch() {
    Circuit* circuit = new Circuit();

    INetworkable* set = circuit->addInput();
    INetworkable* reset = circuit->addInput();

    INetworkable* nor0 = circuit->addComponent(createNOR(), true);
    INetworkable* nor1 = circuit->addComponent(createNOR(), true);

    circuit->connectFrom(reset)->connectTo(nor0, 0);
    circuit->connectFrom(nor1)->connectTo(nor0, 1);

    circuit->connectFrom(nor0)->connectTo(nor1, 0);
    circuit->connectFrom(set)->connectTo(nor1, 1);

    return circuit;
}
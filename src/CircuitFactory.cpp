#include "CircuitFactory.h"

Circuit* CircuitFactory::createXNOR() {
    Circuit* circuit = new Circuit();

    ConstantOutputSource* input0 = circuit->addInput();
    ConstantOutputSource* input1 = circuit->addInput();

    Perceptron* and0 = circuit->addPerceptron(_factory->createAND());
    Perceptron* nor0 = circuit->addPerceptron(_factory->createNOR());
    Perceptron* or0 = circuit->addPerceptron(_factory->createOR(), true);

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

Circuit* CircuitFactory::createXOR() {
    Circuit* circuit = new Circuit();

    ConstantOutputSource* input0 = circuit->addInput();
    ConstantOutputSource* input1 = circuit->addInput();

    Perceptron* or0 = circuit->addPerceptron(_factory->createOR());
    Perceptron* nand0 = circuit->addPerceptron(_factory->createNAND());
    Perceptron* and0 = circuit->addPerceptron(_factory->createAND(), true);

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

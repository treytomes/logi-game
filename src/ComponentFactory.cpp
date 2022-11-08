#include "ComponentFactory.h"

#include "Circuit.h"
#include "Perceptron.h"

#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include "json.hpp"
using json = nlohmann::json;

#include <fstream>
#include <vector>

INetworkable* ComponentFactory::loadFile(string path) {
    ifstream f(path);
    if (!f.good()) {
        throw exception("Unable to read the file.");
    }
    json contents = json::parse(f);
    string name = contents["name"].get<string>();
    string type = contents["type"].get<string>();
    float bias = contents["bias"].get<float>();
    vector<float> weights = contents["weights"].get<vector<float>>();

    if (type == "perceptron") {
        Perceptron* p0 = new Perceptron(weights.size());
        p0->setBias(bias);
        for (int n = 0; n < weights.size(); n++) {
            p0->setWeight(n, weights[n]);
        }
        return p0;
    } else {
        throw exception("Circuit type not implemented.");
    }
}

INetworkable* ComponentFactory::createNOT() {
    return loadFile("./assets/circuits/not.json");
}

INetworkable* ComponentFactory::createAND() {
    return loadFile("./assets/circuits/and.json");
}

INetworkable* ComponentFactory::createOR() {
    return loadFile("./assets/circuits/or.json");
}

INetworkable* ComponentFactory::createNOR() {
    return loadFile("./assets/circuits/nor.json");
}

INetworkable* ComponentFactory::createNAND() {
    return loadFile("./assets/circuits/nand.json");
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
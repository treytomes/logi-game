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

INetworkable* ComponentFactory::createDiode() {
    return loadFile("./assets/circuits/diode.json");
}

INetworkable* ComponentFactory::createXNOR() {
    Circuit* circuit = new Circuit();

    INetworkable* input0 = circuit->addInput();
    INetworkable* input1 = circuit->addInput();

    INetworkable* and0 = circuit->addComponent(createAND());
    INetworkable* nor0 = circuit->addComponent(createNOR());
    INetworkable* or0 = circuit->addComponent(createOR(), true);

    circuit->connectFrom(input0, 0)
        ->connectTo(and0, 0)
        ->connectTo(nor0, 0);
    circuit->connectFrom(input1, 0)
        ->connectTo(and0, 1)
        ->connectTo(nor0, 1);
    circuit->connectFrom(and0, 0)->connectTo(or0, 0);
    circuit->connectFrom(nor0, 0)->connectTo(or0, 1);

    return circuit;
}

INetworkable* ComponentFactory::createXOR() {
    Circuit* circuit = new Circuit();

    INetworkable* input0 = circuit->addInput();
    INetworkable* input1 = circuit->addInput();

    INetworkable* or0 = circuit->addComponent(createOR());
    INetworkable* nand0 = circuit->addComponent(createNAND());
    INetworkable* and0 = circuit->addComponent(createAND(), true);

    circuit->connectFrom(input0, 0)
        ->connectTo(or0, 0)
        ->connectTo(nand0, 0);
    circuit->connectFrom(input1, 0)
        ->connectTo(or0, 1)
        ->connectTo(nand0, 1);
    circuit->connectFrom(or0, 0)->connectTo(and0, 0);
    circuit->connectFrom(nand0, 0)->connectTo(and0, 1);

    return circuit;
}

INetworkable* ComponentFactory::createClock(int stepsPerTick) {
    if (stepsPerTick < 1) {
        throw exception("stepsPerTick must be >= 1");
    }

    Circuit* circuit = new Circuit();
    /**
     * The flip-flop has one extra layer added for the enable line, so that's one more step for the state to settle.
     *
     * RESET is input 0.
     * ENABLE is input 1.
     * SET is input 2.
     * Q! is output 0.
     * Q is output 1.
     */

    if (stepsPerTick == 1) {
        INetworkable* not0 = circuit->addComponent(createNOT(), true);
        circuit->connectFrom(not0, 0)->connectTo(not0, 0);
    } else if (stepsPerTick == 2) {
        //INetworkable* not0 = circuit->addComponent(createNOT());
        //circuit->connectFrom(not0, 0)->connectTo(not0, 0);
        INetworkable* not0 = createClock(1);

        INetworkable* srFlipFlop0 = circuit->addComponent(createSRFlipFlop(), true);
        circuit->connectFrom(not0, 0)->connectTo(srFlipFlop0, 1); // Not to SR Flip-Flop Enable
        circuit->connectFrom(srFlipFlop0, 1)->connectTo(srFlipFlop0, 0); // SR Flip-Flop Q to Reset
        circuit->connectFrom(srFlipFlop0, 0)->connectTo(srFlipFlop0, 2); // SR Flip-Flop Q! to Set

        //INetworkable* diode0 = circuit->addComponent(createDiode(), true);
        //circuit->connectFrom(srFlipFlop0, 1)->connectTo(diode0, 0);
    } else if (stepsPerTick == 3) {
        INetworkable* not0 = circuit->addComponent(createNOT());
        INetworkable* srFlipFlop0 = circuit->addComponent(createSRFlipFlop());
        INetworkable* srFlipFlop1 = circuit->addComponent(createSRFlipFlop(), true);
        //INetworkable* diode0 = circuit->addComponent(createDiode(), true);

        // NOT loops back on itself to generate the clock signal.
        circuit->connectFrom(not0, 0)->connectTo(not0, 0);

        // Not to all enables.
        circuit->connectFrom(not0, 0)->connectTo(srFlipFlop0, 1);
        circuit->connectFrom(not0, 0)->connectTo(srFlipFlop1, 1);

        // Final Q to all resets.
        circuit->connectFrom(srFlipFlop1, 1)->connectTo(srFlipFlop0, 0);
        circuit->connectFrom(srFlipFlop1, 1)->connectTo(srFlipFlop1, 0);

        // Previous Q to current Set.
        circuit->connectFrom(srFlipFlop0, 1)->connectTo(srFlipFlop1, 2);

        // Final Q! to first Set.
        circuit->connectFrom(srFlipFlop1, 0)->connectTo(srFlipFlop0, 2);

        // Final Q to output diode.
        //circuit->connectFrom(srFlipFlop0, 1)->connectTo(diode0, 0);
    }
    /*
    } else if (stepsPerTick == 2) {
        INetworkable* diode0 = circuit->addComponent(createDiode());
        INetworkable* not0 = circuit->addComponent(createNOT(), true);

        circuit->connectFrom(diode0, 0)->connectTo(not0, 0);
        circuit->connectFrom(not0, 0)->connectTo(diode0, 0);
    } else if (stepsPerTick == 3) {
        INetworkable* diode0 = circuit->addComponent(createDiode());
        INetworkable* diode1 = circuit->addComponent(createDiode());
        INetworkable* not0 = circuit->addComponent(createNOT(), true);

        circuit->connectFrom(diode0, 0)->connectTo(diode1, 0);
        circuit->connectFrom(diode1, 0)->connectTo(not0, 0);
        circuit->connectFrom(not0, 0)->connectTo(diode0, 0);
    } else if (stepsPerTick == 4) {
        INetworkable** diode = (INetworkable**)malloc(sizeof(INetworkable*) * (stepsPerTick - 1));
        for (int n = 0; n < stepsPerTick - 1; n++) {
            diode[n] = circuit->addComponent(createDiode());
        }
        INetworkable* not0 = circuit->addComponent(createNOT(), true);

        for (int n = 0; n < stepsPerTick - 2; n++) {
            circuit->connectFrom(diode[n], 0)->connectTo(diode[n + 1], 0);
        }

        circuit->connectFrom(diode[stepsPerTick - 2], 0)->connectTo(not0, 0);
        circuit->connectFrom(not0, 0)->connectTo(diode[0], 0);

        free(diode);
    }
    */

    return circuit;
}

INetworkable* ComponentFactory::createSRLatch() {
    Circuit* circuit = new Circuit();

    INetworkable* set = circuit->addInput();
    INetworkable* reset = circuit->addInput();

    INetworkable* nor0 = circuit->addComponent(createNOR(), true);
    INetworkable* nor1 = circuit->addComponent(createNOR(), true);

    circuit->connectFrom(reset, 0)->connectTo(nor0, 0);
    circuit->connectFrom(nor1, 0)->connectTo(nor0, 1);

    circuit->connectFrom(nor0, 0)->connectTo(nor1, 0);
    circuit->connectFrom(set, 0)->connectTo(nor1, 1);

    return circuit;
}

INetworkable* ComponentFactory::createSRFlipFlop() {
    Circuit* circuit = new Circuit();

    ConstantOutputSource* reset0 = circuit->addInput();
    ConstantOutputSource* enable0 = circuit->addInput();
    ConstantOutputSource* set0 = circuit->addInput();

    INetworkable* and0 = circuit->addComponent(createAND());
    INetworkable* and1 = circuit->addComponent(createAND());

    INetworkable* srLatch0 = circuit->addComponent(createSRLatch());

    INetworkable* qNot0 = circuit->addComponent(createDiode(), true);
    INetworkable* q0 = circuit->addComponent(createDiode(), true);

    circuit->connectFrom(reset0, 0)->connectTo(and0, 0);
    circuit->connectFrom(enable0, 0)->connectTo(and0, 1);
    circuit->connectFrom(enable0, 0)->connectTo(and1, 0);
    circuit->connectFrom(set0, 0)->connectTo(and1, 1);
    circuit->connectFrom(and0, 0)->connectTo(srLatch0, 0);
    circuit->connectFrom(and1, 0)->connectTo(srLatch0, 1);
    circuit->connectFrom(srLatch0, 0)->connectTo(qNot0, 0);
    circuit->connectFrom(srLatch0, 1)->connectTo(q0, 0);

    return circuit;
}

INetworkable* ComponentFactory::createDLatch() {
    Circuit* circuit = new Circuit();

    ConstantOutputSource* d0 = circuit->addInput();
    ConstantOutputSource* e0 = circuit->addInput();

    INetworkable* qNot0 = circuit->addComponent(createDiode(), true);
    INetworkable* q0 = circuit->addComponent(createDiode(), true);

    INetworkable* not0 = circuit->addComponent(createNOT());
    INetworkable* srFlipFlop0 = circuit->addComponent(createSRFlipFlop());

    circuit->connectFrom(d0, 0)->connectTo(not0, 0);
    circuit->connectFrom(d0, 0)->connectTo(srFlipFlop0, 2);
    circuit->connectFrom(e0, 0)->connectTo(srFlipFlop0, 1);

    circuit->connectFrom(not0, 0)->connectTo(srFlipFlop0, 0);

    circuit->connectFrom(srFlipFlop0, 0)->connectTo(qNot0, 0);
    circuit->connectFrom(srFlipFlop0, 1)->connectTo(q0, 0);

    return circuit;
}

INetworkable* ComponentFactory::createCounter() {
    Circuit* circuit = new Circuit();

    //ConstantOutputSource* clk0 = circuit->addInput();


    return circuit;
}
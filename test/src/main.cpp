#include <stdio.h>

#include <algorithm>
#include <exception>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// TODO: Use std::exception.
// TODO: Cost is related to computational complexity.

template<typename TValue>
class AssertException: public exception {
    private:
        TValue _expectedValue;
        TValue _actualValue;

    public:
        AssertException(TValue expectedValue, TValue actualValue)
            : exception(), _expectedValue(expectedValue), _actualValue(actualValue) {
        }

        inline TValue getExpectedValue() { return _expectedValue; }
        inline TValue getActualValue() { return _actualValue; }

        const char* what() {
            stringstream ss;
            ss << "Expected " << getExpectedValue() << ", found " << getActualValue() << ".";
            return ss.str().c_str();
        }
};

template<typename TValue>
class OutOfRangeException: public range_error {
    private:
        TValue _value;
        TValue _minimum;
        TValue _maximum;

    public:
        OutOfRangeException(TValue value, TValue minimum, TValue maximum)
            : range_error(""), _value(value), _minimum(minimum), _maximum(maximum) {
        }

        inline TValue getValue() { return _value; }
        inline TValue getMinimum() { return _minimum; }
        inline TValue getMaximum() { return _maximum; }

        const char* what() {
            stringstream ss;
            ss << getValue() << " must be between " << getMinimum() << " and " << getMaximum() << ".";
            return ss.str().c_str();
        }
};

class ArgumentNullException: public exception {
    private:
        string _argumentName;

    public:
        ArgumentNullException(string argumentName)
            : exception(), _argumentName(argumentName) {
        }

        inline string getArgumentName() { return _argumentName; }

        const char* what() {
            stringstream ss;
            ss << getArgumentName() << " was null.";
            return ss.str().c_str();
        }
};

class IHasOutput {
    public:
        virtual ~IHasOutput() {}
        virtual float getOutput() = 0;
};

class ConstantOutputSource: public IHasOutput {
    private:
        float _output;

    public:
        ConstantOutputSource(float output = 0) : _output(output) {}
        inline float getOutput() { return _output; }
        inline void setOutput(float output) { _output = output; }
};

class Perceptron: public IHasOutput {
    private:
        int _numInputs;
        float _bias;
        float* _weights;
        float* _inputs;

    public:
        Perceptron(int numInputs)
            : _numInputs(numInputs) {
            _weights = new float[_numInputs];
            _inputs = new float[_numInputs];
            clear();
        }

        ~Perceptron() {
            if (_weights != nullptr) {
                delete[] _weights;
                _weights = nullptr;
            }
            if (_inputs != nullptr) {
                delete[] _inputs;
                _inputs = nullptr;
            }
        }    

        inline void clear() {
            _bias = 0;
            for (int n = 0; n < _numInputs; n++) {
                setWeight(n, 0);
                setInput(n, 0);
            }
        }

        inline int getNumInputs() {
            return _numInputs;
        }

        inline void setBias(float value) {
            _bias = value;
        }

        inline float getBias() {
            return _bias;
        }

        inline void setWeight(int n, float value) {
            if ((n < 0) || (n >= getNumInputs())) {
                throw OutOfRangeException(n, 0, getNumInputs());
            }
            _weights[n] = value;
        }

        inline float getWeight(int n) {
            if ((n < 0) || (n >= getNumInputs())) {
                throw OutOfRangeException(n, 0, getNumInputs());
            }
            return _weights[n];
        }

        inline void setInput(int n, float value) {
            if ((n < 0) || (n >= getNumInputs())) {
                throw OutOfRangeException(n, 0, getNumInputs());
            }
            _inputs[n] = value;
        }

        inline float getInput(int n) {
            if ((n < 0) || (n >= getNumInputs())) {
                throw OutOfRangeException(n, 0, getNumInputs());
            }
            return _inputs[n];
        }

        inline float getOutput() {
            float output = 0;
            for (int n = 0; n < getNumInputs(); n++) {
                output += getWeight(n) * getInput(n);
            }
            output += getBias();
            return (output > 0) ? 1 : 0;
        }
};

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

class PerceptronWireConnection {
    private:
        Perceptron* _target;
        int _inputNumber;

    public:
        PerceptronWireConnection(Perceptron* target, int inputNumber)
            : _target(target), _inputNumber(inputNumber) {
            if (target == nullptr) {
                throw ArgumentNullException("target");
            }
        }

        inline Perceptron* getTarget() { return _target; }
        inline int getInputNumber() { return _inputNumber; }
};

class PerceptronWire {
    private:
        IHasOutput* _source;
        vector<PerceptronWireConnection*> _targets;

    public:
        PerceptronWire(IHasOutput* source)
            : _source(source) {
            if (source == nullptr) {
                throw ArgumentNullException("source");
            }
        }

        ~PerceptronWire() {
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                delete *iter;
            }
            _targets.clear();
        }

        inline IHasOutput* getSource() { return _source; }

        inline bool isConnected(Perceptron* target) {
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                PerceptronWireConnection* conn = *iter;
                if (conn->getTarget() == target) {
                    return true;
                }
            }
            return false;
        }

        PerceptronWire* connectTo(Perceptron* target, int inputNumber) {
            if (target == nullptr) {
                throw ArgumentNullException("target");
            }
            if (!isConnected(target)) {
                _targets.push_back(new PerceptronWireConnection(target, inputNumber));
            }
            return this;
        }

        void disconnect(Perceptron* target) {
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                PerceptronWireConnection* conn = *iter;
                if (conn->getTarget() == target) {
                    _targets.erase(iter);
                    break;
                }
            }
        }

        void step() {
            float value = getSource()->getOutput();
            for (auto iter = _targets.begin(); iter != _targets.end(); iter++) {
                PerceptronWireConnection* conn = *iter;
                conn->getTarget()->setInput(conn->getInputNumber(), value);
            }
        }
};

class Circuit {
    private:
        vector<ConstantOutputSource*> _inputs;
        vector<Perceptron*> _perceptrons;
        vector<PerceptronWire*> _wires;
        vector<Perceptron*> _outputs;

    public:
        Circuit() {}

        ~Circuit() {
            for (auto it = _inputs.begin(); it != _inputs.end(); it++) {
                delete *it;
            }
            _inputs.clear();

            for (auto it = _perceptrons.begin(); it != _perceptrons.end(); it++) {
                delete *it;
            }
            _perceptrons.clear();

            for (auto it = _wires.begin(); it != _wires.end(); it++) {
                delete *it;
            }
            _wires.clear();
        }

        ConstantOutputSource* addInput(float value = 0) {
            ConstantOutputSource* input = new ConstantOutputSource(value);
            _inputs.push_back(input);
            return input;
        }

        Perceptron* addPerceptron(Perceptron* perceptron, bool isOutput = false) {
            _perceptrons.push_back(perceptron);
            if (isOutput) {
                _outputs.push_back(perceptron);
            }
            return perceptron;
        }

        void setInput(int inputNumber, float value) {
            if ((inputNumber < 0) || (inputNumber >= (int)_inputs.size())) {
                throw OutOfRangeException(inputNumber, 0, (int)_inputs.size());
            }
            _inputs[inputNumber]->setOutput(value);
        }

        float getOutput(int outputNumber) {
            if ((outputNumber < 0) || (outputNumber >= (int)_outputs.size())) {
                throw OutOfRangeException(outputNumber, 0, (int)_outputs.size());
            }
            return _outputs[outputNumber]->getOutput();
        }

        PerceptronWire* connectFrom(IHasOutput* source) {
            PerceptronWire* wire = new PerceptronWire(source);
            _wires.push_back(wire);
            return wire;
        }

        void step() {
            for (auto it = _wires.begin(); it != _wires.end(); it++) {
                (*it)->step();
            }
        }
};

class TestSuite {
    protected:
        template<typename TValue>
        void assertEqual(TValue expectedValue, TValue actualValue) {
            if (expectedValue != actualValue) {
                throw AssertException(expectedValue, actualValue);
            }
        }

    public:
        virtual ~TestSuite() {}
        virtual void runAll() = 0;
};

template<typename TDerivedClass>
class TestSuiteBase: public TestSuite {
    protected:
        void runTest(string name, void (TDerivedClass::*fn)()) {
            cout << "Running test: " << name << endl;
            try {
                TDerivedClass* derived = (TDerivedClass*)this;
                (derived->*fn)();
                cout << "\\--Passed." << endl;
            } catch (exception& e) {
                cout << "\\--Failed: " << e.what() << endl;
            }
        }

    public:
        virtual ~TestSuiteBase() {}
};

class PerceptronTests: public TestSuiteBase<PerceptronTests> {
    private:
        PerceptronFactory* _factory;

    public:
        PerceptronTests() {
            _factory = new PerceptronFactory();
        }

        ~PerceptronTests() {
            if (_factory != nullptr) {
                delete _factory;
                _factory = nullptr;
            }
        }

        void runAll() {
            runTest("Perceptron ==> NOT", &PerceptronTests::testPerceptronCanBeNOT);
            runTest("Perceptron ==> AND", &PerceptronTests::testPerceptronCanBeAND);
            runTest("Perceptron ==> OR", &PerceptronTests::testPerceptronCanBeOR);
            runTest("Perceptron ==> NOR", &PerceptronTests::testPerceptronCanBeNOR);
            runTest("Perceptron ==> NAND", &PerceptronTests::testPerceptronCanBeNAND);
        }

        void testPerceptronCanBeNOT() {
            Perceptron *p0 = _factory->createNOT();
            try {
                p0->setInput(0, 0);
                assertEqual(1.0f, p0->getOutput());

                p0->setInput(0, 1);
                assertEqual(0.0f, p0->getOutput());
            } catch (exception& e) {
                delete p0;
                throw;
            }

            delete p0;
        }

        void testPerceptronCanBeAND() {
            Perceptron *p0 = _factory->createAND();
            try {
                p0->setInput(0, 0);
                p0->setInput(1, 0);
                assertEqual(0.0f, p0->getOutput());

                p0->setInput(0, 0);
                p0->setInput(1, 1);
                assertEqual(0.0f, p0->getOutput());

                p0->setInput(0, 1);
                p0->setInput(1, 0);
                assertEqual(0.0f, p0->getOutput());

                p0->setInput(0, 1);
                p0->setInput(1, 1);
                assertEqual(1.0f, p0->getOutput());
            } catch (exception& e) {
                delete p0;
                throw;
            }

            delete p0;
        }

        void testPerceptronCanBeOR() {
            Perceptron *p0 = _factory->createOR();
            try {
                p0->setInput(0, 0);
                p0->setInput(1, 0);
                assertEqual(0.0f, p0->getOutput());

                p0->setInput(0, 0);
                p0->setInput(1, 1);
                assertEqual(1.0f, p0->getOutput());

                p0->setInput(0, 1);
                p0->setInput(1, 0);
                assertEqual(1.0f, p0->getOutput());

                p0->setInput(0, 1);
                p0->setInput(1, 1);
                assertEqual(1.0f, p0->getOutput());
            } catch (exception& e) {
                delete p0;
                throw;
            }

            delete p0;
        }

        void testPerceptronCanBeNOR() {
            Perceptron *p0 = _factory->createNOR();
            try {
                p0->setInput(0, 0);
                p0->setInput(1, 0);
                assertEqual(1.0f, p0->getOutput());

                p0->setInput(0, 0);
                p0->setInput(1, 1);
                assertEqual(0.0f, p0->getOutput());

                p0->setInput(0, 1);
                p0->setInput(1, 0);
                assertEqual(0.0f, p0->getOutput());

                p0->setInput(0, 1);
                p0->setInput(1, 1);
                assertEqual(0.0f, p0->getOutput());
            } catch (exception& e) {
                delete p0;
                throw;
            }

            delete p0;
        }

        void testPerceptronCanBeNAND() {
            Perceptron *p0 = _factory->createNAND();
            try {
                p0->setInput(0, 0);
                p0->setInput(1, 0);
                assertEqual(1.0f, p0->getOutput());

                p0->setInput(0, 0);
                p0->setInput(1, 1);
                assertEqual(1.0f, p0->getOutput());

                p0->setInput(0, 1);
                p0->setInput(1, 0);
                assertEqual(1.0f, p0->getOutput());

                p0->setInput(0, 1);
                p0->setInput(1, 1);
                assertEqual(0.0f, p0->getOutput());
            } catch (exception& e) {
                delete p0;
                throw;
            }

            delete p0;
        }
};

class CircuitTests: public TestSuiteBase<CircuitTests> {
    private:
        PerceptronFactory* _factory;

    public:
        CircuitTests() {
            _factory = new PerceptronFactory();
        }

        ~CircuitTests() {
            if (_factory != nullptr) {
                delete _factory;
                _factory = nullptr;
            }
        }

        void runAll() {
            runTest("Circuit ==> XNOR", &CircuitTests::testCircuitXNOR);
            runTest("Circuit ==> XOR", &CircuitTests::testCircuitXOR);
        }

        void testCircuitXNOR() {
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

            // There are 2 layers, so we need 1 update for the circuit to settle.

            input0->setOutput(0);
            input1->setOutput(0);
            circuit->step();
            assertEqual(1.0f, circuit->getOutput(0));

            input0->setOutput(0);
            input1->setOutput(1);
            circuit->step();
            assertEqual(0.0f, circuit->getOutput(0));

            input0->setOutput(1);
            input1->setOutput(0);
            circuit->step();
            assertEqual(0.0f, circuit->getOutput(0));

            input0->setOutput(1);
            input1->setOutput(1);
            circuit->step();
            assertEqual(1.0f, circuit->getOutput(0));

            delete circuit;
        }


        void testCircuitXOR() {
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

            // There are 2 layers, so we need 1 update for the circuit to settle.

            input0->setOutput(0);
            input1->setOutput(0);
            circuit->step();
            assertEqual(0.0f, circuit->getOutput(0));

            input0->setOutput(0);
            input1->setOutput(1);
            circuit->step();
            assertEqual(1.0f, circuit->getOutput(0));

            input0->setOutput(1);
            input1->setOutput(0);
            circuit->step();
            assertEqual(1.0f, circuit->getOutput(0));

            input0->setOutput(1);
            input1->setOutput(1);
            circuit->step();
            assertEqual(0.0f, circuit->getOutput(0));

            delete circuit;
        }
};

int main(int argc, char* argv[]) {
    try {
        TestSuite* tests;
        
        tests = new PerceptronTests();
        tests->runAll();
        delete tests;

        tests = new CircuitTests();
        tests->runAll();
        delete tests;
    } catch (exception& e) {
        cerr << "An error occurred." << endl;
        cerr << e.what() << endl;
    }
    return 0;
}

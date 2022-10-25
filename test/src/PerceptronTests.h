#ifndef __PERCEPTRONTESTS_H__
#define __PERCEPTRONTESTS_H__

#include <exception>
using namespace std;

#include "Perceptron.h"
#include "PerceptronFactory.h"
#include "TestSuiteBase.h"

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

#endif

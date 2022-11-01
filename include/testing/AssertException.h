#ifndef __ASSERTEXCEPTION_H__
#define __ASSERTEXCEPTION_H__

#include <exception>
#include <sstream>
using namespace std;

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

        inline const char* what() {
            stringstream ss;
            ss << "Expected " << getExpectedValue() << ", found " << getActualValue() << ".";
            return ss.str().c_str();
        }

        void assert() {
            if (getExpectedValue() != getActualValue()) {
                throw *this;
            }
        }
};

#endif

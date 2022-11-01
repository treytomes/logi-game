#ifndef __OUTOFRANGEEXCEPTION_H__
#define __OUTOFRANGEEXCEPTION_H__

#include <exception>
#include <sstream>
using namespace std;

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

        inline const char* what() {
            stringstream ss;
            ss << getValue() << " must be between " << getMinimum() << " and " << getMaximum() << ".";
            return ss.str().c_str();
        }

        inline void assert() {
            if ((getValue() < getMinimum()) || (getValue() >= getMaximum())) {
                throw *this;
            }
        }
};

#endif

#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include "AssertException.h"

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

#endif

#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include "AssertException.h"

class TestSuite {
    protected:
        template<typename TValue>
        inline void assertEqual(TValue expectedValue, TValue actualValue) {
            AssertException(expectedValue, actualValue).assert();
        }

    public:
        virtual ~TestSuite() {}
        virtual void runAll() = 0;
};

#endif

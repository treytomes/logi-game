#ifndef __ARGUMENTNULLEXCEPTION_H__
#define __ARGUMENTNULLEXCEPTION_H__

#include <exception>
#include <sstream>
#include <string>
using namespace std;

class ArgumentNullException: public exception {
    private:
        string _argumentName;

    public:
        ArgumentNullException(string argumentName)
            : exception(), _argumentName(argumentName) {
        }

        inline string getArgumentName() { return _argumentName; }

        inline const char* what() {
            stringstream ss;
            ss << getArgumentName() << " was null.";
            return ss.str().c_str();
        }
};

#endif

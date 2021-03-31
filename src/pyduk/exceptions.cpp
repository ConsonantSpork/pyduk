#include <cstring>
#include "exceptions.hpp"

namespace pyduk {
    ConversionException::ConversionException(std::string message) : msg(message)
    {}

    const char* ConversionException::what() const throw() {
        char* ret = new char[msg.length() + 1];
        strcpy(ret, msg.c_str());
        return ret;
    }
}

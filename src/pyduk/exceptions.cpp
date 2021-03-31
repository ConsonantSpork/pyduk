#include <cstring>
#include "exceptions.hpp"

namespace pyduk {
    DukException::DukException(std::string message) : msg(message)
    {}

    DukException::~DukException()
    {}  // Implement virtual destructor so derived classes do not have to

    const char* DukException::what() const throw() {
        char* ret = new char[msg.length() + 1];
        strcpy(ret, msg.c_str());
        return ret;
    }
}

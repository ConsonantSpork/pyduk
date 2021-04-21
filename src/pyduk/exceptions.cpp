#include <cstring>
#include <utility>
#include "exceptions.hpp"

namespace pyduk {
    DukException::DukException(std::string message) : msg(std::move(message))
    {}

    DukException::~DukException() = default;  // Implement virtual destructor so derived classes do not have to

    const char* DukException::what() const noexcept {
        char* ret = new char[msg.length() + 1];
        strcpy(ret, msg.c_str());
        return ret;
    }
}

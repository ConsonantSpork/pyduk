#pragma once

#include <string>
#include <exception>

namespace pyduk {
    /** @brief Base exception for  */
    class DukException : public std::exception {
        public:
            /** @brief Constructs exception from a message.
             *
             * @param msg message describing exception. */
            DukException(std::string msg);
            virtual ~DukException() = 0;  // Prohibit class instantiation. Note that destructor is
                                          // still implemented, so derived classes do not have to do it.

            /** @brief Get exception description.
             *
             * @returns String describing exception. */
            const char* what() const throw();

        private:
            std::string msg;
    };

    /** @brief Exception thrown on unsuccessful conversion from JavaScript types to Python objects. */
    class ConversionException : public DukException {
        public:
            ConversionException(std::string msg) : DukException(msg) {}
    };

    /** @brief Exception thrown on errors when running JavaScript. */
    class RuntimeException : public DukException {
        public:
            RuntimeException(std::string msg) : DukException(msg) {}
    };
}

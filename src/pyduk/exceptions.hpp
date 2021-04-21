#pragma once

#include <string>
#include <exception>
#include <utility>

namespace pyduk {
    /** @brief Base exception for  */
    class DukException : public std::exception {
        public:
            /** @brief Constructs exception from a message.
             *
             * @param msg message describing exception. */
            explicit DukException(std::string msg);
            virtual ~DukException() = 0;  // Prohibit class instantiation. Note that destructor is
                                          // still implemented, so derived classes do not have to do it.

            /** @brief Get exception description.
             *
             * @returns String describing exception. */
            virtual const char* what() const noexcept;

        private:
            std::string msg;
    };

    /** @brief Exception thrown on unsuccessful conversion from JavaScript types to Python objects. */
    class ConversionException : public DukException {
        public:
            explicit ConversionException(std::string msg) : DukException(std::move(msg)) {}
    };

    /** @brief Exception thrown on errors when running JavaScript. */
    class RuntimeException : public DukException {
        public:
            explicit RuntimeException(std::string msg) : DukException(std::move(msg)) {}
    };
}

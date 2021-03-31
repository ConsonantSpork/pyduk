#pragma once

#include <string>
#include <exception>

namespace pyduk {
    /** @brief Exception thrown on conversion from JavaScript types to Python objects. */
    class ConversionException : public std::exception {
        public:
            /** @brief Constructs ConversionException from a message.
             *
             * @param msg message describing exception. */
            ConversionException(std::string msg);

            /** @brief Get exception description.
             *
             * @returns String describing exception. */
            const char* what() const throw();
        private:
            std::string msg;
    };
}

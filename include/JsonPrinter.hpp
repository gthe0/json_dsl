#ifndef JSONPRINTER_HPP
#define JSONPRINTER_HPP

#include <iostream>
#include <JsonVar.hpp>

namespace jsonlang
{
    // Printer
    struct JsonVarPrinter {
        JsonVarPrinter() = default;

        JsonVarPrinter& operator,(const JsonVar& var) {
            std::cout << var.toString();
            return *this;
        }

        JsonVarPrinter& operator,(const std::vector<JsonVar> vars) {
            for (const JsonVar& v : vars)
                std::cout << v.toString();
            return *this;
        }
    };
} // namespace jsonlang

#endif //! JSONPRINTER_HPP
#ifndef JSONPRINTER_HPP
#define JSONPRINTER_HPP

#include <iostream>
#include <JsonVar.hpp>

namespace jsonlang
{
    // Singleton Printer
    class JsonVarPrinter {
    public:
        // Delete copy constructor and assignment operator
        JsonVarPrinter(const JsonVarPrinter&) = delete;
        JsonVarPrinter& operator=(const JsonVarPrinter&) = delete;

        static JsonVarPrinter& getInstance() {
            static JsonVarPrinter printer;
            return printer;
        }

        JsonVarPrinter& operator,(const JsonVar& var) {
            std::cout << var.toString();
            return *this;
        }

    private:
        JsonVarPrinter() = default;
    };

} // namespace jsonlang

#endif //! JSONPRINTER_HPP


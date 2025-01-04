#ifndef JSONERASER_HPP
#define JSONERASER_HPP

#include <iostream>
#include <JsonVar.hpp>

namespace jsonlang
{
    // ERASER
    struct JsonVarEraser {
        JsonVarEraser() = default;

        JsonVarEraser& operator,(const JsonVar& var) {
            std::cout << var.toString();
            return *this;
        }

        JsonVarEraser& operator,(const std::vector<JsonVar> vars) {
            for (const JsonVar& v : vars)
                std::cout << v.toString();
            return *this;
        }
    };
} // namespace jsonlang

#endif //! JSONERASER_HPP
#ifndef JSONERASER_HPP
#define JSONERASER_HPP

#include <JsonVar.hpp>
#include <map>

namespace jsonlang
{
// Singleton Eraser
class JsonVarEraser {
public:
    // Delete copy constructor and assignment operator
    JsonVarEraser(const JsonVarEraser&) = delete;
    JsonVarEraser& operator=(const JsonVarEraser&) = delete;

    // Static method to get the instance
    static JsonVarEraser& getInstance() {
        static JsonVarEraser eraser;
        return eraser;
    }

    // Overload operator to erase based on JsonRef
    JsonVarEraser& operator=(JsonVar& var) {
        var.erase();
        return *this;
    }
private:
    // Private constructor to prevent instantiation
    JsonVarEraser() = default;
};

} // namespace jsonlang

#endif //! JSONERASER_HPP


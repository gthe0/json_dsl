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

    // Method to add a reference
    JsonVar& operator=(JsonVar& var) {

        if(var.type_ == JsonVar::kArray || var.type_ == JsonVar::kObject)
        {
            referenceMap.insert({ nextId++,var });
            var.setReferenceId(nextId);

            if(var.type_ == JsonVar::kArray) var.ArrayRefIdSetter();
            else                             var.ObjectRefCountSetter();
        }

        return var; 
    }

    // Method to add a reference
    JsonVar& operator+=(JsonVar& var) {

        if (var.type_ == JsonVar::kArray || var.type_ == JsonVar::kObject)
        {
            var.setReferenceId(nextId);
            referenceMap.insert({ nextId,var });

            if (var.type_ == JsonVar::kArray) var.ArrayRefIdSetter();
            else                              var.ObjectRefCountSetter();
        }

        return var;
    }

    // Overload operator to erase based on JsonRef
    JsonVarEraser& operator,(JsonVar& JsonRef) {

        return *this;
    }
private:
    // Private constructor to prevent instantiation
    JsonVarEraser() = default;

    // Map to store references
    std::map<int, JsonVar&> referenceMap;

    int nextId = 0;
};

} // namespace jsonlang

#endif //! JSONERASER_HPP


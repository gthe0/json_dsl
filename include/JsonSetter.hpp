#ifndef JSONSETTER_HPP
#define JSONSETTER_HPP

#include <JsonVar.hpp>
#include <JsonSetOperations.hpp>

namespace jsonlang
{

class JsonVarSetter {
public:
    // Delete copy constructor and assignment operator
    JsonVarSetter(const JsonVarSetter&) = default;
    JsonVarSetter& operator=(const JsonVarSetter&) = delete;

    JsonVarSetter& operator=(JsonVar& var) {
        lhs = &var;
        return *this;
    }

    JsonVarSetter& operator,(const JsonVar& var) {
        if(lhs == nullptr) {
            throw std::runtime_error("Error: SETTER cannot be used without a left hand side value!"); 
        }
        return *this;
    }

    JsonVarSetter& operator,(const std::vector<JsonVar>& vars) {
        if(lhs == nullptr) {
            throw std::runtime_error("Error: SETTER cannot be used without a left hand side value!"); 
        }
        return *this;
    }

private:
    JsonVar* lhs = nullptr;
};

} // namespace jsonlang

#endif //! JSONSETTER_HPP


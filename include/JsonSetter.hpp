#ifndef JSONSETTER_HPP
#define JSONSETTER_HPP

#include <JsonVar.hpp>
#include <JsonSetCommands.hpp>

namespace jsonlang
{

class JsonVarSetter {
public:

    JsonVarSetter() = default;
    // Delete copy constructor and assignment operator
    JsonVarSetter(const JsonVarSetter&) = default;
    JsonVarSetter& operator=(const JsonVarSetter&) = delete;

    JsonVarSetter& operator=(JsonVar& var) {
        
        if(lhs != nullptr) {
            throw std::runtime_error("Error: SET is used only with 1 argument!"); 
        }

        lhs = &var;
        return *this;
    }

    JsonVarSetter& operator,(JsonVar& var) {

        if(command == nullptr && lhs != nullptr) {
            throw std::runtime_error("Error: SET does not accept multiple arguments!"); 
        }

        command->execute(lhs,var);
        return *this;
    }

    JsonVarSetter& operator,(SetCommand& var) {

        if(command != nullptr) {
            throw std::runtime_error("Error: SET multiple commands defined!"); 
        }

        if(lhs == nullptr) {
            throw std::runtime_error("Error: SET was not given a left handside value!"); 
        }

        command = &var;
        return *this;
    }


private:
    JsonVar* lhs = nullptr;
    SetCommand* command = nullptr;
};

} // namespace jsonlang

#endif //! JSONSETTER_HPP


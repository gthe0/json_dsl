#ifndef JSONSETCOMMANDS_HPP
#define JSONSETCOMMANDS_HPP

#include <JsonVar.hpp>

namespace jsonlang
{

class SetCommand
{
public:
    virtual void execute(JsonVar* lhs,JsonVar& rhs) = 0;
};

class AssignSetCommand: public SetCommand
{
public:
    void execute(JsonVar* lhs,JsonVar& rhs) override
    {
        if(hasSet == true)
        {
            throw std::runtime_error("Error: Assignment of multiple values is prohibited");
        }

        /*Complete the Code here*/
        

        hasSet = true;
    }
private:
    bool hasSet = false;
};

class AppendSetCommand: public SetCommand
{
public:
    void execute(JsonVar* lhs,JsonVar& rhs) override
    {
        JsonVar& lval = lhs->extractVal();
        JsonVar& rval = rhs.extractVal();

        if (lval.type_ != JsonVar::kArray)
        {
            throw std::runtime_error("Error: Append operation can only be used with an Array");
        }

        bool doesExist = false;
        for (const JsonVar& lhs_value : lval.array_) {
            if (lhs_value.isEqual(rval))
            {
                doesExist = true;
                break;
            }
        }
        if (!doesExist) lval.array_.push_back(rval);
    }
};

} // namespace jsonlang

#endif //! JSONSETCOMMANDS_HPP


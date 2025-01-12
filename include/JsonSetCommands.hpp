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

        if (lhs->type_ == JsonVar::kObjectNode)
        {
            auto& map = lhs->objectNode_.first.object_; // Access the map
            const auto& key = lhs->objectNode_.second;  // Access the key 
            
            if (map.find(key) == map.end()) {
                map.insert({key, JsonVar()});
            }
        }

        JsonVar& lval = lhs->extractVal();
        JsonVar& rval = rhs.extractVal();
        
        lval.cleanup();
        lval.type_ = rval.type_;
        
        switch (lval.type_)
        {
        case (JsonVar::kString): new (&lval.str_) JsonVar::JsonString(rval.str_); break;
        case (JsonVar::kNumber): lval.num_ = rval.num_; break;
        case (JsonVar::kBoolean): lval.bool_ = rval.bool_; break;
        case (JsonVar::kObject): new (&lval.object_) JsonVar::JsonObject(rval.object_); break;
        case (JsonVar::kArray): new (&lval.array_) JsonVar::JsonArray(rval.array_); break;
        default: break;
        }

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
    
        lval.array_.push_back(rval);
    }
};

} // namespace jsonlang

#endif //! JSONSETCOMMANDS_HPP


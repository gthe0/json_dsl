#ifndef JSONVAR_HPP
#define JSONVAR_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

#include <json_kv_pair.hpp>

namespace jsonlang
{

class JsonVar
{
    // Json definitions 
    using JsonString = std::string;
    using JsonArray  = std::vector<JsonVar>;
    using JsonObject = std::map<std::string,JsonVar>;

public:

    // Constructors
    explicit JsonVar()               : type_(JsonVar::kNull), num_(0) {}
    explicit JsonVar(int num)        : type_(JsonVar::kNumber), num_(num) {}
    explicit JsonVar(double num)     : type_(JsonVar::kNumber), num_(num) {}
    explicit JsonVar(bool boolean)   : type_(JsonVar::kBoolean), bool_(boolean) {}
    explicit JsonVar(JsonString  str): type_(JsonVar::kString), str_(std::move(str)) {}
    explicit JsonVar(std::initializer_list<KeyValue> kv_list):
        type_(JsonVar::kObject) 
    {
        new(&kvmap_) JsonObject();
        for (const auto& kv_pair: kv_list)
        {
            kvmap_.insert({ kv_pair.key_,*(kv_pair.var_) });
        }
    }
    
    // Copy constructor
    JsonVar(const JsonVar &other): num_(0) {
        cleanup();
        type_ = other.type_;
        switch (type_)
        {
            case kString: new (&str_) JsonString(other.str_); break;
            case kNumber: num_ = other.num_; break;
            case kBoolean: bool_ = other.bool_; break;
            case kObject: new (&kvmap_) JsonObject(other.kvmap_); break;
            case kArray: new (&array_) JsonArray(other.array_); break;
            default: break;
        }
    }

   ~JsonVar() { cleanup(); };

    // Overloaded Operators
   // Implicit number to JsonVar conversion is prohibited
   // If the number passed is 0 then I assume that is a NULL
    JsonVar& operator=(int num)
    {
        if(num != NULL)
        {
            std::cerr << "Error: Implicit Number to JsonVar convertion is prohibited!\n";
        }

        cleanup();
        type_ = JsonVar::kNull;
        return *this;
    }

    // Copy operator
    JsonVar& operator=(const JsonVar& other)
    {
        cleanup();
        type_ = other.type_;
        switch (type_)
        {
        case kString: new (&str_) JsonString(other.str_); break;
        case kNumber: num_ = other.num_; break;
        case kBoolean: bool_ = other.bool_; break;
        case kObject: new (&kvmap_) JsonObject(other.kvmap_); break;
        case kArray: new (&array_) JsonArray(other.array_); break;
        default: break;
        }

        return *this;
    }

    // Turn to String based on type
    JsonString toString() const
    {
        JsonString result;

        switch (type_)
        {
            case kString:   result = str_; break;
            case kNumber:   result = std::to_string(num_); break;
            case kBoolean:  result = bool_ ? "true" : "false"; break;
            case kObject:
            {
                result = "{ ";

                for (const auto &pair_ : kvmap_)
                {
                    result += "\"" + pair_.first + "\": " + pair_.second.toString() + ", ";
                }

                result += " }";
                break;
            }
            case kArray:
            {
                JsonString result = "[ ";
                for (size_t i = 0; i < array_.size(); ++i) {
                    result += array_[i].toString();
                    if (i < array_.size() - 1) {
                        result += ", ";
                    }
                }
                result += " ]";
                break;
            }
            default: result = "null";
        }

        return result;
    }

private:

    // All Json Types
    enum
    {
        kNull,
        kNumber,
        kString,
        kBoolean,
        kObject,
        kArray
    } type_;
    
    // All the values that a JsonVar can hold
    union
    {   
        bool        bool_;
        double      num_;
        JsonString  str_;
        JsonObject  kvmap_;
        JsonArray   array_;
    };

    // Cleanup function for union types
    void cleanup()
    {
        switch (type_)
        {
            // These are the only Objects to cleanup
            case kString:   str_.~basic_string(); break;
            case kObject:   kvmap_.~map();        break;
            case kArray:    array_.~vector();     break;
            default: return;
        }
    }
};

} // namespace jsonlang

#endif //! JSONVAR_HPP


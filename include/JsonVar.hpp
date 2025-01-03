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
    explicit JsonVar()               : type_(JsonVar::kObject) { new(&object_) JsonObject(); }
    explicit JsonVar(double num)     : type_(JsonVar::kNumber), num_(num) {}
    explicit JsonVar(bool boolean)   : type_(JsonVar::kBoolean), bool_(boolean) {}
    explicit JsonVar(JsonString  str): type_(JsonVar::kString), str_(std::move(str)) {}
    explicit JsonVar(int a, int b)   : type_(JsonVar::kArray)
    {
        new (&array_) JsonArray();
    }
    explicit JsonVar(std::initializer_list<KeyValue> kv_list):
        type_(JsonVar::kObject) 
    {
        new(&object_) JsonObject();
        for (const auto& kv_pair: kv_list)
        {
            object_.insert({ kv_pair.key_,*(kv_pair.var_) });
        }
    }

    
    // Copy constructor
    JsonVar(const JsonVar &other): num_(0) {
        type_ = other.type_;
        switch (type_)
        {
            case kString: new (&str_) JsonString(other.str_); break;
            case kNumber: num_ = other.num_; break;
            case kBoolean: bool_ = other.bool_; break;
            case kObject: new (&object_) JsonObject(other.object_); break;
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
        case kObject: new (&object_) JsonObject(other.object_); break;
        case kArray: new (&array_) JsonArray(other.array_); break;
        default: break;
        }

        return *this;
    }


    // BEGIN: These are used for Array Creation and Printing
    JsonArray operator,(const JsonVar& rhs)
    {
        return {*this, rhs};
    }

    JsonArray operator,(JsonArray rhs)
    {
        rhs.push_back(*this);
        return rhs;
    }

    JsonVar& operator[](JsonArray rhs)
    {
        cleanup();
        
        type_ = JsonVar::kArray;
        array_ = std::move(rhs);

        return *this;
    }

    JsonVar& operator[](const JsonVar& rhs)
    {
        cleanup();

        type_ = JsonVar::kArray;
        array_.push_back(rhs);
        return *this;
    }
    // END


    // BEGIN
    //
    // Eq operator
    //
    // The comparisons of the various objects
    // are already defined in the standard and thus
    // are implemented
    JsonVar operator==(const JsonVar& rvalue)
    {
        if( rvalue.type_ != type_ ) return JsonVar(false);

        bool result = false;
        switch (type_)
        {
            case kNumber:    result = (rvalue.num_   == num_);  break;
            case kString:    result = (rvalue.str_   == str_); break;
            case kBoolean:   result = (rvalue.bool_  == bool_); break;
            /*case kArray:     result = (rvalue.array_ == array_); break;
            case kObject:    result = (rvalue.object_ == object_); break;
            */default: result = true;
        }

        return JsonVar(result);
    }

    JsonVar operator!=(const JsonVar& rvalue)
    {
        JsonVar result = (*this == rvalue);
        result.bool_ = !result.bool_;
        return result;
    }

    JsonVar operator&&(const JsonVar& rvalue)
    {
        if(type_ != JsonVar::kBoolean || rvalue.type_ != type_)
        {
            std::cerr << "Error: logical operators can\
                          only be used between booleans" << std::endl;

            exit(EXIT_FAILURE);
        }

        return JsonVar(rvalue.bool_ && bool_);
    }

    JsonVar operator||(const JsonVar& rvalue)
    {
        if(type_ != JsonVar::kBoolean || rvalue.type_ != type_)
        {
            std::cerr << "Error: logical operators can\
                          only be used between booleans" << std::endl;

            exit(EXIT_FAILURE);
        }

        return JsonVar(rvalue.bool_ || bool_);
    }

    JsonVar operator!()
    {
        if(type_ != JsonVar::kBoolean)
        {
            std::cerr << "Error: logical operators can\
                          only be used between booleans" << std::endl;

            exit(EXIT_FAILURE);
        }

        return JsonVar(!bool_);
    }

    //END Logical operators


    // BEGIN Arithmentic operators
    
    JsonVar operator*(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
            std::cerr << "Error: arithmentic operators can\
                          only be used between numbers" << std::endl;

            exit(EXIT_FAILURE);
        }

        return JsonVar(static_cast<double>(number.num_ * num_));
    }

    JsonVar operator/(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
            std::cerr << "Error: arithmentic operators can\
                          only be used between numbers" << std::endl;

            exit(EXIT_FAILURE);
        }

        return JsonVar(static_cast<double>(number.num_ / num_));
    }

    JsonVar operator-(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
            std::cerr << "Error: arithmentic operators can\
                          only be used between numbers" << std::endl;

            exit(EXIT_FAILURE);
        }

        return JsonVar(static_cast<double>(number.num_ - num_));
    }

    JsonVar operator%(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
            std::cerr << "Error: arithmentic operators can\
                          only be used between numbers" << std::endl;

            exit(EXIT_FAILURE);
        }

        // It can only be used between integers
        return JsonVar(
            static_cast<double>(
            static_cast<int>(number.num_) % static_cast<int>(num_)));
    }

    JsonVar operator>(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
            std::cerr << "Error: arithmentic operators can\
                          only be used between numbers" << std::endl;

            exit(EXIT_FAILURE);
        }

        return JsonVar(number.num_ > num_);
    }

    JsonVar operator<(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
            std::cerr << "Error: arithmentic operators can\
                          only be used between numbers" << std::endl;

            exit(EXIT_FAILURE);
        }

        return JsonVar(number.num_ < num_);
    }

    JsonVar operator>=(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
            std::cerr << "Error: arithmentic operators can\
                          only be used between numbers" << std::endl;

            exit(EXIT_FAILURE);
        }

        return JsonVar(number.num_ >= num_);
    }

    JsonVar operator<=(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
            std::cerr << "Error: arithmentic operators can\
                          only be used between numbers" << std::endl;

            exit(EXIT_FAILURE);
        }

        return JsonVar(number.num_ <= num_);
    }

    // END Arithmentic operators




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

                for (const auto &pair_ : object_)
                {
                    result += "\"" + pair_.first + "\": " + pair_.second.toString() + ", ";
                }

                result += " }";
                break;
            }
            case kArray:
            {
                result = "[ ";
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
        JsonObject  object_;
        JsonArray   array_;
    };

    // Cleanup function for union types
    void cleanup()
    {
        switch (type_)
        {
            // These are the only Objects to cleanup
            case kString:   str_.~basic_string(); break;
            case kObject:   object_.~map();        break;
            case kArray:    array_.~vector();     break;
            default: return;
        }
    }
};

} // namespace jsonlang

#endif //! JSONVAR_HPP


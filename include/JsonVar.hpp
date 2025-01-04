#ifndef JSONVAR_HPP
#define JSONVAR_HPP

#include <map>
#include <vector>
#include <string>
#include <stdexcept>
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
            throw std::runtime_error("Error: Implicit Number to JsonVar convertion is prohibited!");
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
        if (this->isEqual(rhs))
            return { *this };
        else
            return {*this, rhs};
    }

    JsonArray operator,(JsonArray rhs)
    {
        for (const auto& temp : rhs)
        {
            if (this->isEqual(temp)) return rhs;
        }

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

    JsonVar& operator[](const JsonVar rhs)
    {   
        cleanup();

        type_ = JsonVar::kArray;
        array_.push_back(rhs);
        return *this; 
    }
    // END

    // BEGIN Access Operators
    JsonVar& operator[](const int index)
    {
        if (type_ != kArray)
        {
            throw std::runtime_error("The Json Variable is not an Array!");
        }

        if (index >= array_.size() || index < 0)
        {
            throw std::runtime_error("Array out of bounds");
        }

        return array_[index];
    }

    JsonVar& operator[](const std::string name)
    {
        if (type_ != kObject)
        {
            throw std::runtime_error("The Json Variable is not an Object!");
        }

        auto it = object_.find(name);
        if (it == object_.end()) 
        { 
            throw std::runtime_error("Key not found in JSON object!");
        } 
        
        return it->second;
    }
    // END Access Operators

    // BEGIN
    //
    // Eq operator
    //
    // The comparisons of the various objects
    // are already defined in the standard and thus
    // are implemented
    JsonVar operator==(const JsonVar& rvalue)
    {
        bool result = isEqual(rvalue);
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
             throw std::runtime_error( "Error: logical operators can only be used between booleans");
        }

        return JsonVar(rvalue.bool_ && bool_);
    }

    JsonVar operator||(const JsonVar& rvalue)
    {
        if(type_ != JsonVar::kBoolean || rvalue.type_ != type_)
        {
             throw std::runtime_error( "Error: logical operators can only be used between booleans");
        }

        return JsonVar(rvalue.bool_ || bool_);
    }

    JsonVar operator!()
    {
        if(type_ != JsonVar::kBoolean)
        {
            throw std::runtime_error("Error: logical operators can only be used between booleans");
        }

        return JsonVar(!bool_);
    }

    //END Logical operators


    // BEGIN Arithmentic operators
    
    JsonVar operator*(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");
        }

        return JsonVar(static_cast<double>(number.num_ * num_));
    }

    JsonVar operator/(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");
        }

        return JsonVar(static_cast<double>(number.num_ / num_));
    }

    JsonVar operator-(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers" );
        }

        return JsonVar(static_cast<double>(number.num_ - num_));
    }

    JsonVar operator%(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");          
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
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");            
        }

        return JsonVar(number.num_ > num_);
    }

    JsonVar operator<(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");
        }

        return JsonVar(number.num_ < num_);
    }

    JsonVar operator>=(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers" );
        }

        return JsonVar(number.num_ >= num_);
    }

    JsonVar operator<=(const JsonVar& number)
    {
        if(type_ != JsonVar::kNumber || type_!=number.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");
        }

        return JsonVar(number.num_ <= num_);
    }

    // END Arithmentic operators

    // BEGIN + Operator
    
    JsonVar operator+(const JsonVar& rhs)
    {
        if (rhs.type_ != type_)
        {
            throw std::runtime_error("Error, Cannot use + with Variables of different types!");
        }
    
        switch (type_)
        {
            case kNumber:
                {
                    return JsonVar(static_cast<double>(rhs.num_ + num_));
                }
            case kString:   
                {
                    return JsonVar(static_cast<std::string>(rhs.str_ + str_));
                }
            case kArray:  
                {
                    JsonVar temp = *this;

                    for (const JsonVar& rhs_value : rhs.array_) {
                        bool doesExist = false;
                        for (const JsonVar& lhs_value : temp.array_) {
                            if(lhs_value.isEqual(rhs_value))
                            {
                                doesExist = true;
                                break;
                            }
                        }
                        if(!doesExist) temp.array_.push_back(rhs_value);
                    }

                    return temp;
                }
            case kObject:
                {
                    JsonVar temp = *this;
                    for (const auto& pair : rhs.object_)
                    {
                        temp.object_.insert(pair);
                    }
                    return temp; 
                }
        default:
            throw std::runtime_error("Error, Cannot use + with NULL or Booleans!");
        }
    
        return JsonVar();
    }

    // END   + Operator 

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

    auto getType() { return type_; }



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

    // Equality checks
    bool isEqual(const JsonVar& rvalue) const
    {
        if (rvalue.type_ != type_) return false;
    
        bool result = false;
        switch (type_)
        {
        case kNumber:    result = (rvalue.num_ == num_);  break;
        case kString:    result = (rvalue.str_ == str_); break;
        case kBoolean:   result = (rvalue.bool_ == bool_); break;
        case kArray:     result = ArrayEq(rvalue.array_); break;
        case kObject:    result = ObjectEq(rvalue.object_); break;
        default: result = true;
        }
    
        return result;
    }

    // Check Object Equality
    bool ObjectEq(const JsonObject& object) const
    {
        if (type_ != JsonVar::kObject)       return false;
        if (object_.size() != object.size()) return false;

        for (const auto& pair : object_)
        {
            auto it = object.find(pair.first);
            
            if (it == object.end() || !(pair.second.isEqual(it->second))) 
                return false;
        }

        return true;
    }

    // Check Array Equality
    bool ArrayEq(const JsonArray& array) const
    {
        if (type_ != JsonVar::kArray)      return false;
        if (array_.size() != array.size()) return false;

        for (size_t i = 0; i < array.size(); i++)
        {
            if (!array_[i].isEqual(array[i])) return false;
        }

        return true;
    }
};

} // namespace jsonlang

#endif //! JSONVAR_HPP


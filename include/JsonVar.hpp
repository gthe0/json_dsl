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

    using JsonArrayNode = std::pair<JsonVar&,int>;
    using JsonObjectNode = std::pair<JsonVar&,std::string>;

public:

    JsonVar(std::nullptr_t)          :type_(JsonVar::kNull), num_(0){}
    // Constructors
    explicit JsonVar()               : type_(JsonVar::kObject) { new(&object_) JsonObject(); }
    explicit JsonVar(double num)     : type_(JsonVar::kNumber), num_(num){}
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
            case kObjectNode: new (&objectNode_) JsonObjectNode(other.objectNode_); break;
            case kArrayNode: new (&arrayNode_) JsonArrayNode(other.arrayNode_); break;
            default: break;
        }
    }

   ~JsonVar() { cleanup(); };

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
    JsonVar operator[](const int index)
    {
        JsonVar& array_node = extractVal();
        if (array_node.type_ != kArray)
        {
            throw std::runtime_error("The Json Variable is not an Array!");
        }

        JsonVar node = JsonVar();
        node.cleanup();

        node.type_ = kArrayNode;
        new (&node.arrayNode_) JsonArrayNode({array_node, index});

        return node;
    }

    JsonVar operator[](const std::string name)
    {
        JsonVar& obj_node = extractVal();
        if (obj_node.type_ != kObject)
        {
            throw std::runtime_error("The Json Variable is not an Object!");
        }

        JsonVar node = JsonVar();
        node.cleanup();

        node.type_ = kObjectNode;
        new (&node.objectNode_) JsonObjectNode({obj_node, name });

        return node;
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
        const JsonVar& lval = extractVal();
        const JsonVar& rval = rvalue.extractVal();

        bool result = lval.isEqual(rval);
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
        const JsonVar& lval = extractVal();
        const JsonVar& rval = rvalue.extractVal();

        if(lval.type_ != JsonVar::kBoolean || lval.type_ != rval.type_)
        {
             throw std::runtime_error( "Error: logical operators can only be used between booleans");
        }

        return JsonVar(lval.bool_ && rval.bool_);
    }

    JsonVar operator||(const JsonVar& rvalue)
    {
        const JsonVar& lval = extractVal();
        const JsonVar& rval = rvalue.extractVal();

        if(lval.type_ != JsonVar::kBoolean || lval.type_ != rval.type_)
        {
             throw std::runtime_error( "Error: logical operators can only be used between booleans");
        }

        return JsonVar(lval.bool_ || rval.bool_);
    }

    JsonVar operator!()
    {
        const JsonVar& lval = extractVal();

        if(lval.type_ != JsonVar::kBoolean)
        {
            throw std::runtime_error("Error: logical operators can only be used between booleans");
        }

        return JsonVar(!lval.bool_);
    }

    //END Logical operators


    // BEGIN Arithmentic operators
    
    JsonVar operator*(const JsonVar& number)
    {
        const JsonVar& lval = extractVal();
        const JsonVar& rval = number.extractVal();

        if(lval.type_ != JsonVar::kNumber || lval.type_!=rval.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");
        }

        return JsonVar(static_cast<double>(lval.num_ * rval.num_));
    }

    JsonVar operator/(const JsonVar& number)
    {
        const JsonVar& lval = extractVal();
        const JsonVar& rval = number.extractVal();

        if(lval.type_ != JsonVar::kNumber || lval.type_!=rval.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");
        }

        return JsonVar(static_cast<double>(lval.num_ / rval.num_));
    }

    JsonVar operator-(const JsonVar& number)
    {
        const JsonVar& lval = extractVal();
        const JsonVar& rval = number.extractVal();

        if(lval.type_ != JsonVar::kNumber || lval.type_!=rval.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers" );
        }

        return JsonVar(static_cast<double>(static_cast<double>(lval.num_ - rval.num_)));
    }

    JsonVar operator%(const JsonVar& number)
    {
        const JsonVar& lval = extractVal();
        const JsonVar& rval = number.extractVal();

        if(lval.type_ != JsonVar::kNumber || lval.type_!=rval.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");          
        }

        // It can only be used between integers
        return JsonVar(
            static_cast<double>(
            static_cast<int>(lval.num_) % static_cast<int>(rval.num_)));
    }

    JsonVar operator>(const JsonVar& number)
    {
        const JsonVar& lval = extractVal();
        const JsonVar& rval = number.extractVal();

        if(lval.type_ != JsonVar::kNumber || lval.type_!=rval.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");            
        }

        return JsonVar(lval.num_ > rval.num_);
    }

    JsonVar operator<(const JsonVar& number)
    {
        const JsonVar& lval = extractVal();
        const JsonVar& rval = number.extractVal();

        if(lval.type_ != JsonVar::kNumber || lval.type_!=rval.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");
        }

        return JsonVar(lval.num_ < rval.num_);
    }

    JsonVar operator>=(const JsonVar& number)
    {
        const JsonVar& lval = extractVal();
        const JsonVar& rval = number.extractVal();

        if(lval.type_ != JsonVar::kNumber || lval.type_!=rval.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers" );
        }

        return JsonVar(lval.num_ >= rval.num_);
    }

    JsonVar operator<=(const JsonVar& number)
    {
        const JsonVar& lval = extractVal();
        const JsonVar& rval = number.extractVal();

        if(lval.type_ != JsonVar::kNumber || lval.type_!=rval.type_)
        {
             throw std::runtime_error( "Error: arithmentic operators can only be used between numbers");
        }

        return JsonVar(lval.num_ <= rval.num_);
    }

    // END Arithmentic operators

    // BEGIN + Operator
    
    JsonVar operator+(const JsonVar& rvalue)
    {
        const JsonVar& lval = extractVal();
        const JsonVar& rhs = rvalue.extractVal();

        if (rhs.type_ != lval.type_)
        {
            throw std::runtime_error("Error, Cannot use + with Variables of different types!");
        }
    
        switch (lval.type_)
        {
            case kNumber:
                {
                    return JsonVar(static_cast<double>(rhs.num_ + lval.num_));
                }
            case kString:   
                {
                    return JsonVar(static_cast<std::string>(rhs.str_ + lval.str_));
                }
            case kArray:  
                {
                    JsonVar temp = lval;

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
                    JsonVar temp = lval;
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
            case kArrayNode:
            case kObjectNode:
            {
                const JsonVar& node = extractVal();
                result = node.toString();

                break;
            }
            default: result = "null";
        }
        return result;
    }

    // BEGIN Utility functions

    // Return the type of the variable
    JsonString typeOf()
    {
        std::string result;

        switch (type_)
        {
        case kNumber:       result = "number";  break;
        case kString:       result = "string"; break;
        case kBoolean:      result = "boolean"; break;
        case kArray:        result = "array"; break;
        case kObject:       result = "object"; break;
        case kNull:         result = "null"; break;
        case kObjectNode:   result = "temp"; break;
        case kArrayNode:    result = "temp"; break;
        default:            result = "";
        }

        return (result);
    }

    // Returns whether a key is found in an object
    bool hasKey(std::string Key)
    {
        if (type_ != JsonVar::kObject)  return false;
        return (object_.find(Key) != object_.end());
    }
    
    // Checks whether an array or an object is empty
    bool isEmpty()
    {
        if (type_ == JsonVar::kObject)          return  (object_.empty());
        if (type_ == JsonVar::kArray)           return  (array_.empty());
            
        return (false);
    }

    size_t sizeOf()
    {
        if (type_ == kObject) return (object_.size());
        if (type_ == kArray)  return (array_.size());
            
        return (1);
    }
    
    void erase()
    {
        switch (type_)
        {
        case kObject:     object_.clear(); break;
        case kArray:      array_.clear(); break;
        case kArrayNode:  ArrayNodeErasure(); break;
        case kObjectNode: objectNode_.first.object_.erase(objectNode_.second); break;
        default:
            throw std::runtime_error("Error: erase can only be used with Arrays, Objects and their Nodes!");
        }
    }
    
    // END Utility functions

private:

    // All Json Types
    enum
    {
        kNull,
        kNumber,
        kString,
        kBoolean,
        kObject,
        kArray,
        kArrayNode,
        kObjectNode,
    } type_;

    // All the values that a JsonVar can hold
    union
    {   
        bool            bool_;
        double          num_;
        JsonString      str_;
        JsonObject      object_;
        JsonArray       array_;
        JsonArrayNode   arrayNode_;
        JsonObjectNode  objectNode_;
    };

    JsonVar &extractVal() const {

        // If it's a Node, we need to extract it first
        if (type_ == kArrayNode)
        {
            if (arrayNode_.second < arrayNode_.first.array_.size() || 0 <= arrayNode_.first.array_.size())
            {
                throw std::runtime_error("Array out of bounds");
            }

            return arrayNode_.first.array_[arrayNode_.second];
        } 
        else if (type_ == kObjectNode) 
        {
            auto it = objectNode_.first.object_.find(objectNode_.second);
            if (it == objectNode_.first.object_.end()) 
            {
                throw std::runtime_error("Error: Key not found in JSON object!");
            }

            return it->second;
        }

        return *(JsonVar*)this;
    }

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

    void ArrayNodeErasure()
    {
        if (type_ != kArrayNode)
        {
            throw std::runtime_error("This function can only be used with an Array Node!");
        }

        if (arrayNode_.second < 0 || arrayNode_.second > arrayNode_.first.sizeOf())
        {
            throw std::runtime_error("Array out of bounds");
        }

        std::vector<JsonVar> newVec;
        newVec.reserve(arrayNode_.first.sizeOf() - 1);

        for (size_t i = 0; i < arrayNode_.first.sizeOf(); ++i)
        {
            if (i != arrayNode_.second) newVec.push_back(arrayNode_.first.array_[i]);
        }

        arrayNode_.first.array_ = std::move(newVec);
    }
};


} // namespace jsonlang

#endif //! JSONVAR_HPP


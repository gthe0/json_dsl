#ifndef JSON_DSL_HPP
#define JSON_DSL_HPP

#include <vector>
#include <string>

namespace jsonlang{

// Forward Declare
class JsonVariable ;
using JsonVector =  std::vector<JsonVariable*>;

// Define a common interface for all Objects
class JsonVariable {
public:
    virtual             ~JsonVariable() = 0;

    // They are different in every class
    virtual std::string typeOf()                 const {return "";}
    virtual std::string toString()               const {return "";}

    // Mostly the same in all of the derived classes
    virtual size_t      sizeOf()                 const { return 1; }
    virtual bool        isEmpty()                const { return false; }
    virtual bool        hasKey(std::string key)  const { return false; }

};

// Destructor Declaration
inline JsonVariable::~JsonVariable(){}

// JsonKey is Used only in the object construction
class JsonKey {
public:
     JsonKey(std::string key): var_(NULL), key_(key) {}
     
    // Used for the object construction
    JsonKey& operator=(JsonVariable* var)
    {
        var_ = var;
        return *this;
    }

    JsonVariable*   var_;
    std::string     key_;
};

class JsonString : public JsonVariable {
public:
    // Constructors
    JsonString(std::string value): value_(value){}    

    // String Specific functions
    std::string typeOf()        const override { return "string";}
    std::string toString()      const override { return value_;}
private:
    std::string value_;
};

class JsonNumber : public JsonVariable {
public:
    // Constructors
    JsonNumber(double value): value_(value){}    

    // Number Specific functions
    std::string typeOf()        const override { return "number";}
    std::string toString()      const override { return std::to_string(value_);}
private:
    double value_;
};

class JsonBoolean : public JsonVariable {
public:

    // Destructors
    ~JsonBoolean() = default;

    // Constructors
    JsonBoolean(bool value): value_(value){}    

    // Boolean Specific functions
    std::string typeOf()        const override { return "boolean";}
    std::string toString()      const override { return std::to_string(value_);}
private:
    bool value_;
};

class JsonObject : public JsonVariable {
public:
    // Destructor
    ~JsonObject() = default; 
    
    // Constructor Based on JsonKey initializer list
    JsonObject() = default;
    JsonObject(std::initializer_list<JsonKey> kv_list) {
        for (auto kv_pair : kv_list){
            bool keyFound = false;
            for (auto& pairs : kvmap_) {
                if(pairs.key_ == kv_pair.key_) {
                    pairs.var_ = kv_pair.var_;
                    keyFound = true;
                    break;
                } 
            }

            // If the key was not found, then this must be
            // a new entry of the map
            if (!keyFound) {
                kvmap_.push_back(kv_pair);
            }
        } 
    }

    std::string typeOf()                 const override{ return "object";}
    bool        hasKey(std::string key)  const override
    {
        // Check if the pair exists
        for (const auto& pairs : kvmap_) {
            if(pairs.key_ == key) return true;
        }

        return false;
    }

    // Implement toString to display the array
    std::string toString() const override {
        std::string result = "{ ";
        for (const auto &pair : kvmap_) {
            result += "\"" + pair.key_ + "\": " + pair.var_->toString() + ", ";
        }
        result += "}";
        return result;
    }

private:
    std::vector<JsonKey> kvmap_;
};

class JsonArray : public JsonVariable {
public:
    ~JsonArray()
    {
        for(auto ptr: array_) delete ptr;
    }

    // Implement toString to display the array
    std::string toString() const override {
        std::string result = "[ ";
        for (size_t i = 0; i < array_.size(); ++i) {
            result += array_[i]->toString();
            if (i < array_.size() - 1) {
                result += ", ";
            }
        }
        result += " ]";
        return result;
    }


    // This functions does not work properly currently
    template <typename... JsonVars>
    JsonArray& operator[](JsonVars*... var_list) {
        addHelper(var_list...);
        return *this;
    }

    size_t      sizeOf() const override { return array_.size();}
    std::string typeOf() const override { return "array";}
private:
    JsonVector array_;

    void addHelper() 
    { /* Base case for recursion - do nothing */}

    template <typename First, typename... Rest>
    void addHelper(First* first, Rest*... rest) {
        array_.push_back(first);
        addHelper(rest...);
    }
};

// Used to create a JsonArray Object and bypass
// problems caused by new[] overloading
inline JsonArray& createJsonArray(void)
{ return *(new JsonArray()); }

} // namespace jsonlang

#endif // json_dsl lib

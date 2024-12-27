#ifndef JSON_DSL_HPP
#define JSON_DSL_HPP

#include <list>
#include <vector>
#include <string>

namespace jsonlang{

#define PROGRAM_BEGIN int main(void) {
#define PROGRAM_END \
    ;return 0; }

#define JSON(var)   ;jsonlang::JsonVariable* var

#define KEY(var)    jsonlang::JsonKey(#var) = 0 ? 0

// Variable Values
#define STRING(var) new jsonlang::JsonString(var)
#define NUMBER(var) new jsonlang::JsonNumber(var)
#define TRUE        new jsonlang::JsonBoolean(true)
#define FALSE       new jsonlang::JsonBoolean(false)
#define OBJECT      new jsonlang::JsonObject

// Macros that call members
#define HAS_KEY (var,key)   var == NULL ? new jsonlang::JsonBoolean(false) :new jsonlang::JsonBoolean(var->hasKey(key))
#define IS_EMPTY(var)       var == NULL ? new jsonlang::JsonBoolean(false) :new jsonlang::JsonBoolean(var->isEmpty())
#define SIZE_OF (var)       var == NULL ? NUMBER(1)      :NUMBER(var->sizeOf())
#define TYPE_OF (var)       var == NULL ? STRING("null") :STRING(var->typeOf())

// Define a common interface for all Objects
class JsonVariable {
public:
    virtual             ~JsonVariable() = 0;

    // They are different in every class
    virtual std::string typeOf()                 const {return "";}
    virtual std::string toString()               const {return "";}

    // Mostly the same in all of the derived classes
    virtual int         sizeOf()                 const { return 1; }
    virtual bool        isEmpty()                const { return false; }
    virtual bool        hasKey(std::string key)  const { return false; }

};

// Destructor Declaration
inline JsonVariable::~JsonVariable(){}

// JsonKey is Used only in the object construction
class JsonKey {
public:
     JsonKey(std::string key): key_(key) {}
     
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

    int         sizeOf() const override { return array_.size();}
    std::string typeOf() const override { return "array";}
private:
    std::vector<JsonVariable*> array_;
};

// Create a JsonList
inline std::list<JsonVariable*> operator,(JsonVariable& a, JsonVariable& b)
{
    std::list<JsonVariable*> json_list{};

    json_list.push_back(&a);
    json_list.push_back(&b);

    return json_list;
}


// Prepend JsonList
inline std::list<JsonVariable*> operator,(JsonVariable* a, std::list<JsonVariable*>& b)
{
    b.push_front(a);
    return (std::move(b));
}

// Append JsonList
inline std::list<JsonVariable*> operator,(std::list<JsonVariable*>& b,JsonVariable* a)
{
    b.push_back(a);
    return (std::move(b));
}

}

#endif // json_dsl lib

#ifndef JSON_DSL_HPP
#define JSON_DSL_HPP

#include <map>
#include <vector>
#include <string>

#define PROGRAM_BEGIN int main(void) {
#define PROGRAM_END \
    ;return 0; }

#define JSON(var)   ;JsonVariable var

// Variable Values
#define STRING(var) JsonString(var)
#define NUMBER(var) JsonNumber(var)
#define TRUE        JsonBoolean(true)
#define FALSE       JsonBoolean(false)

// Undef NULL whose default value is (void*)0x0
#undef  NULL
#define NULL        JsonNull()

// Macros that call members
#define HAS_KEY (var,key)   var.hasKey(key) 
#define SIZE_OF (var)       var.sizeof()
#define IS_EMPTY(var)       var.isEmpty()
#define TYPE_OF (var)       var.typeOf()

// Define a common interface for all Objects
class JsonVariable {
public:
    virtual             ~JsonVariable() = default;

    // They are different in every class
    virtual std::string typeOf()        const {return "";}  
    virtual std::string valueToString() const {return "";}

    // Mostly the same in all of the derived classes
    virtual bool        isEmpty() const { return 1; }
    virtual int         sizeOf()  const { return 1; }
    virtual bool        hasKey(std::string key)  const { return false; }
};

class JsonString : public JsonVariable {
public:
    // Constructors
    JsonString(std::string value): value_(value){}    

    // String Specific functions
    std::string typeOf()        const { return "string";}
    std::string valueToString() const { return value_;}
private:
    std::string value_;
};

class JsonNumber : public JsonVariable {
public:
    // Constructors
    JsonNumber(double value): value_(value){}    

    // Number Specific functions
    std::string typeOf()        const { return "number";}
    std::string valueToString() const { return std::to_string(value_);}
private:
    double value_;
};

class JsonBoolean : public JsonVariable {
public:
    // Constructors
    JsonBoolean(bool value): value_(value){}    

    // Boolean Specific functions
    std::string typeOf()        const { return "boolean";}
    std::string valueToString() const { return std::to_string(value_);}
private:
    bool value_;
};


class JsonNull : public JsonVariable {
public:
    std::string typeOf()        const { return "null";}
    std::string valueToString() const { return "null";}
};

class JsonObject : public JsonVariable {
public:
    std::string typeOf() const { return "object";}
private:
    std::map<std::string, JsonVariable> kvmap_;
};

class JsonArray : public JsonVariable {
public:
    std::string typeOf() const { return "array";}
private:
    std::vector<JsonVariable> array_;
};


#endif // json_dsl lib

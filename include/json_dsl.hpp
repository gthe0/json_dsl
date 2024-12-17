#ifndef JSON_DSL_HPP
#define JSON_DSL_HPP

#include <map>
#include <vector>
#include <string>

#define PROGRAM_BEGIN int main(void) {
#define PROGRAM_END \
    return 0; }


// Define a common interface for all Objects
class JsonVariable {
public:
    virtual             ~JsonVariable() = default;
    virtual std::string typeOf() const  = 0;

    // Mostly the same in all of the derived classes
    virtual bool        isEmpty() const { return 1; }
    virtual int         sizeOf()  const { return 1; }
    virtual bool        hasKey()  const { return false; }
};

class JsonString : public JsonVariable {
public:
    std::string typeOf() const { return "string";}
private:
    std::string value_;
};

class JsonNumber : public JsonVariable {
public:
    std::string typeOf() const { return "number";}
private:
    double value_;
};

class JsonBoolean : public JsonVariable {
public:
    std::string typeOf() const { return "boolean";}
private:
    bool value_;
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

class JsonNull : public JsonVariable {
public:
    std::string typeOf() const { return "null";}
private:
};


#endif // json_dsl lib

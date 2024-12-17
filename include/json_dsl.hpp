#ifndef JSON_DSL_HPP
#define JSON_DSL_HPP

#include <string>

#define PROGRAM_BEGIN int main(void) {
#define PROGRAM_END \
    return 0; }


// Define a common interface for all Objects
class JsonVariable {
public:
    virtual             ~JsonVariable() = default;
    virtual std::string typeOf()        = 0;

    // Mostly the same in all of the derived classes
    virtual bool        isEmpty()       { return 1; }
    virtual int         sizeOf()        { return 1; }
    virtual bool        hasKey()        { return false; }
};

class JsonString : public JsonVariable {
public:
private:
};

class JsonNumber : public JsonVariable {
public:
private:
};

class JsonBoolean : public JsonVariable {
public:
private:
};

class JsonObject : public JsonVariable {
public:
private:
};

class JsonArray : public JsonVariable {
public:
private:
};

#endif // json_dsl lib

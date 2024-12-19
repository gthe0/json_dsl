#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <stdarg.h>
#include <map>

#define PROGRAM_BEGIN int main() { 
#define PROGRAM_END ; return 0;}

#define STRING(x) x
#define NUMBER(x) x
#define TRUE true
#define FALSE false
#define OBJECT Object
#define KEY(name) Key(#name)=(0>1)?0

#define concat(x, y) x##y

#define JSON(name) ; Json name; name(#name)

class Key {
public:
    std::string key;
    int ival = 0;
    std::string sval;

    Key(std::string k) : key(k) {}

    Key& operator=(int arg) {
        ival = arg;
        return *this;
    }

    Key& operator=(std::string arg) {
        sval = arg;
        return *this;
    }
};

class Object {
private:
    std::map<std::string, void*> mp;

public:
    Object(std::initializer_list<Key> args) {
        for (const auto& arg : args) {
            if(arg.ival != 0)
                std::cout << arg.key << " " << arg.ival << std::endl;
            else if(!arg.sval.empty())
                std::cout << arg.key << " " << arg.sval << std::endl;
        }
    }
};

struct ObjectBuilder {
    void operator=(std::initializer_list<Key> args) {
        Object obj(args);
    }
};

class Json {
private:
    std::string name;
    std::string sval;
    int ival;
    double dval;
    bool bval;
    Object oval();
    std::list<Json> array;

public:
    static std::list<Json> jsonList;

    void display() const {
        std::cout << jsonList.back().name << std::endl;
    }

    Json& operator()(std::string name) {
        Json json;
        json.name = name;
        jsonList.emplace_back(json);
        return *this;
    }

    Json& operator=(int arg) {
        jsonList.back().ival = arg;
        return *this;
    }

    Json& operator=(std::string arg) {
        jsonList.back().sval = arg;
        return *this;
    }

    Json& operator=(double arg) {
        jsonList.back().dval = arg;
        return *this;
    }

    Json& operator=(bool arg) {
        jsonList.back().bval = arg;
        return *this;
    }

    Json& operator=(Object arg) {
        //std::cout <<  << std::endl;
        //jsonList.back().oval() = arg;
        return *this;
    }
};


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

class Object;

class Key {
public:
    enum class Type { Null, Int, String, Double, Object };     
    Type type = Type::Null;

    std::string key;
    int ival;
    std::string sval; 
    double dval;
    Object* oval;

    Key() {}
    Key(std::string k) : key(k) {}

    Key& operator=(int arg) {
        ival = arg;
        type = Type::Int;
        return *this;
    }

    Key& operator=(std::string arg) {
        sval = arg;
        type = Type::String;
        return *this;
    }

    Key& operator=(double arg) {
        dval = arg;
        type = Type::Double;
        return *this;
    }

    Key& operator=(Object* arg) {
        oval = arg;
        type = Type::Object;
        return *this;
    }
};

class Object {
private:
    std::map<std::string, Key> mp;

public:
    Object() {}
    Object(std::initializer_list<Key> args) {
        for (const auto& arg : args) {
            switch(arg.type) {
                case Key::Type::Int:
                    mp[arg.key] = arg.ival;
                    break;
                case Key::Type::String:
                    mp[arg.key] = arg.sval;
                    break;
                case Key::Type::Double:
                    mp[arg.key] = arg.dval;
                    break;
            }
        }
    }

    std::map<std::string, Key> getMap() {return mp;}
};

class Json {
private:
    std::string name;
    std::string sval;
    int ival;
    double dval;
    bool bval;
    Object oval;
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
        jsonList.back().oval = arg;    
        return *this;
    }
};


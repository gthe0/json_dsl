#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <stdarg.h>

#define PROGRAM_BEGIN int main() { 
#define PROGRAM_END ; return 0;}

#define STRING(x) #x
#define NUMBER(x) x
#define TRUE true
#define FALSE false
//#define NULL nullptr

#define concat(x, y) x##y

#define JSON(name) ; Json name; name(#name)

class OBJECT {
private:
    typedef struct pairstruct {
        std::string key;
        void* value;
    }pair;
    pair* next;

public:
    OBJECT(std::initializer_list<std::string> args) {
        for (const auto& arg : args) {
            std::cout << arg << std::endl;
        }
    }
};

struct ObjectBuilder {
    void operator=(std::initializer_list<std::string> args) {
        OBJECT obj(args);
    }
};

class Json {
private:
    std::string name;
    std::string sval;
    int ival;
    double dval;
    bool bval;
    OBJECT oval();
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

    Json& operator=(OBJECT arg) {
        //jsonList.back().oval() = arg;
        return *this;
    }
};


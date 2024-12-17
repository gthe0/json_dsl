#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <stdarg.h>

#define STRING(x) #x;
#define NUMBER(x) x;
#define TRUE true;
#define FALSE false;
//#define NULL nullptr;

#define concat(x, y) x##y

#define JSON(name) JSON json; json(#name)
#define OBJECT(...) createObject(__VA_ARGS__);

class OBJECT {
private:
    typedef struct pairstruct {
        std::string key;
        void* value;
    }pair;
    pair* next;
};

class JSON {
private:
    std::string name;
    std::string sval;
    int ival;
    double dval;
    bool bval;
    OBJECT object;
    std::list<JSON> array;

public:
    static std::list<JSON> jsonList;

    void display() const {
        std::cout << jsonList.back().bval << std::endl;
    }

    JSON& operator()(std::string name) {
        JSON json;
        json.name = name;
        jsonList.emplace_back(json);
        return *this;
    }

    void operator=(int arg) {
        jsonList.back().ival = arg;
    }

    void operator=(std::string arg) {
        jsonList.back().sval = arg;
    }

    void operator=(double arg) {
        jsonList.back().dval = arg;
    }

    void operator=(bool arg) {
        jsonList.back().bval = arg;
    }

    
};


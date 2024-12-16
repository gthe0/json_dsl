#include <iostream>
#include <list>
#include <string>

#define STRING(x) #x;
#define INTEGER(x) x;
#define TRUE true;
#define FALSE false;
//#define NULL null;

#define concat(x, y) x##y

#define JSON(name) JSON json; json(#name);

class JSON {
private:
    std::string name;
    std::string sval;
    int ival;
    double dval;
    bool bval;
    typedef struct object {
        int ival;
        double dval;
        std::string sval;
    }oval;
    std::list<JSON> array;

public:
    static std::list<JSON> jsonList;

    void display() const {
        std::cout << name << "\n";
    }

    void operator()(std::string name) {
        JSON json;
        json.name = name;
        jsonList.emplace_back(json);
    }

    
};


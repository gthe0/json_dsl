#ifndef JSON_DSL_HPP
#define JSON_DSL_HPP

#include <list>
#include <vector>
#include <string>
#include <iostream>

#define PROGRAM_BEGIN int main(void) {
#define PROGRAM_END ;return 0; }

#define JSON(var)   ;Json var

// Variable Values
#define STRING(var) Json(var)
#define NUMBER(var) Json(var)
#define TRUE Json(1)
#define FALSE Json(0)
#define OBJECT Json
#define KEY(var) Json(#var) = 0 ? 0
#define ARRAY Json()

#define SET ;
#define ASSIGN /=

struct Json {
private:
    enum class Type { Null, String, Number };     
    Type type = Type::Null;

    std::string sval;
    double nval;
    
    struct Object {
        std::string key;
        Json *value;
    } oval;
    std::vector<Object> olist;

    std::vector<Json> jlist;

public:
    Json() = default;

    Json(std::string s) : sval(s) { type = Type::String; oval.key = s; }

    Json(double n) : nval(n) { type = Type::Number; }

    Json(std::initializer_list<Json> list) {
        for (auto var : list) {
            olist.push_back(var.oval);
        }
    }

    Json& operator=(Json var) {
        oval.value = new Json(var);
        return *this;
    }

    Json& operator[](Json var) {
        auto temp_list = std::move(var.jlist);
        
        jlist.push_back(var);

        for (const auto& ref : temp_list) {
            jlist.push_back(ref);
        }

        return *this;
    }
    
    Json& operator,(Json var) {
        jlist.push_back(var);
        return *this;
    }

    Json& operator[](std::string arg) {     // SET OBJECT
        sval = arg;
        return *this;
    }

    Json& operator[](int arg) {     // SET ARRAY
        nval = arg;
        return *this;
    }

    Json& operator/=(Json var) {
        if(this != &var) {
            if(type == Type::String || type == Type::Number) {
                type = var.type;
                sval = var.sval;
                nval = var.nval;
                olist = var.olist;
                jlist = var.jlist;
            } else if(!jlist.empty()) {     // SET ARRAY
                jlist[nval].sval = sval;
                jlist[nval] /= var;
            } else {                        // SET OBJECT
                if(var.olist.empty()) {
                    int exists = 0;
                    for (auto& pair : olist) {
                        if(pair.key == sval) {
                            exists = 1;
                            pair.value = new Json(var);
                        }
                    }
                    if(exists == 0) {
                        oval.key = sval;
                        oval.value = new Json(var);
                        olist.push_back(oval);
                    }
                } else {
                    int exists = 0;
                    for (auto& pair : olist) {
                        if(pair.key == sval) {
                            exists = 1;
                            pair.value = new Json(var);
                        }
                    }
                    if(exists == 0) {
                        if(olist.empty())
                            olist = var.olist;
                        else {
                            oval.key = sval;
                            oval.value = new Json(var);
                            olist.push_back(oval);                           
                        }
                    }
                    
                }
            }
        }
        return *this;
    }

    std::string toString() {
        if(type == Type::String) return sval;
        else if(type == Type::Number) return std::to_string(nval);
        else if(!olist.empty()) {
            std::string result = "{ ";
            for (const auto& pair : olist) {
                if(&pair == &olist.back())
                    result += "\"" + pair.key + "\": " + pair.value->toString();
                else
                    result += "\"" + pair.key + "\": " + pair.value->toString() + ", ";
            }
            result += " }";
            return result;
        }
        else if(!jlist.empty()) {
            std::string result = "[ ";
            for (auto& var : jlist) {
                if(&var == &jlist.back())
                    result += var.toString();
                else
                    result += var.toString() + ", ";
            }
            result += " ]";
            return result;
        }
        return "NULL";
    }
};

/* inline std::vector<Json> operator,(Json a, std::vector<Json> jlist) {
    std::vector<Json> json_list {};

    json_list.push_back(a);
    

    return json_list;
} */

#endif
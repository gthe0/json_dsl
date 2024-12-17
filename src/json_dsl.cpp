#include "../include/json_dsl.hpp"

std::list<JSON> JSON::jsonList;

template <typename... Things>
void createObject(Things... things) {
    for (const auto p : {things...}) {
        std::cout << p << std::endl;
    }
}

int main(int argc, char *argv[]) { 

    JSON(obj) = NUMBER(10)
    OBJECT("test", "test1", "test2")

    for (const auto& jsonObj : JSON::jsonList) {
        jsonObj.display();
    }

    return 0; 
}

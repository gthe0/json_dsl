#include <json_dsl.hpp>

std::list<JSON> JSON::jsonList;

int main(int argc, char *argv[]) { 
    JSON(obj)

    for (const auto& jsonObj : JSON::jsonList) {
        jsonObj.display();
    }

    return 0; 
}



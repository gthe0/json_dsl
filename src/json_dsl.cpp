#include "../include/json_dsl.hpp"

std::list<Json> Json::jsonList;

PROGRAM_BEGIN

    JSON(obj) = NUMBER(10)
    JSON(test) = OBJECT{ 
        KEY(test1):NUMBER(10), 
        KEY(test2):STRING("test"),
        KEY(test3):OBJECT{
                KEY(obj1):NUMBER(5),
                KEY(obj2):TRUE
            }
        }

    ;Json json
    ;json.display()

PROGRAM_END

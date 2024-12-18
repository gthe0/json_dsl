#include "../include/json_dsl.hpp"

std::list<Json> Json::jsonList;

PROGRAM_BEGIN

    JSON(obj) = NUMBER(10)
    JSON(test) = OBJECT{"test"}

PROGRAM_END

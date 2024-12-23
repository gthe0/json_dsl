#include <json_dsl.hpp>

PROGRAM_BEGIN
    JSON(obj1) = STRING("hello")
    JSON(obj2) = NULL
    JSON(obj3) = TRUE
    JSON(obj4) = FALSE
    JSON(obj5) = NUMBER(3.324);
PROGRAM_END

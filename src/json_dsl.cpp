#include "json_dsl.hpp"

PROGRAM_BEGIN

    JSON(obj1) = ARRAY[STRING("TEST"), STRING("TEST2"), STRING("TEST3")]
    //std::cout << obj1.toString() << std::endl;

PROGRAM_END
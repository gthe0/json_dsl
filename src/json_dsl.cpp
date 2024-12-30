#include "json_dsl.hpp"

PROGRAM_BEGIN

    JSON(obj1) = ARRAY[STRING("test"), OBJECT{KEY(key3):NUMBER(10)}]
    SET obj1[1]["key5"] ASSIGN OBJECT{KEY(key8):NUMBER(1)};
    std::cout << obj1.toString() << std::endl;

PROGRAM_END
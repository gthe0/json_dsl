#include <JsonLang.hpp>
#include <iostream>

PROGRAM_BEGIN


    JSON(obj0) = OBJECT {
        KEY(key)  : STRING("Hello"),
        KEY(key1) : STRING("WORLD"),
        KEY(key2) : OBJECT{ KEY(key1):NUMBER(1)}
    }

    JSON(obj1) = OBJECT {KEY(key)  : STRING("Hello")}
    SET obj1 ASSIGN obj0
    SET obj1 ASSIGN NULL

    JSON(obj2) = TRUE;
    

    std::cout << obj0.toString() << std::endl;
    std::cout << obj1.toString() << std::endl;
    std::cout << obj2.toString() << std::endl; 

PROGRAM_END

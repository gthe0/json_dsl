#include <json_dsl.hpp>
#include <iostream>

PROGRAM_BEGIN
    JSON(obj7) = OBJECT {
        KEY(key)  : STRING("Hello"),
        KEY(key1) : STRING("WORLD"),
        KEY(key2) : OBJECT{ KEY(key1):NUMBER(1)}
    };

    JSON(obj8) = OBJECT {KEY(key)  : STRING("Hello")};
    
    std::cout << obj7->toString() << std::endl; 
    std::cout << obj8->toString() << std::endl; 

PROGRAM_END

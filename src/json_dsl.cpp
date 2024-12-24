#include <json_dsl.hpp>
#include <iostream>

PROGRAM_BEGIN
    JSON(obj6) = ARRAY[STRING("A"),STRING("B")]
    JSON(obj7) = OBJECT {
        KEY(key)  : STRING("Hello"),
        KEY(key1) : STRING("WORLD"),
        KEY(key2) : OBJECT{ KEY(key1):NUMBER(1)}
    };
    
    std::cout << obj7->toString() << std::endl; 
    std::cout << obj6->toString() << std::endl; 

PROGRAM_END

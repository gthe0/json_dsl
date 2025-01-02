#include <JsonLang.hpp>

PROGRAM_BEGIN

    JSON(obj0) = OBJECT {
        KEY(key)  : STRING("Hello"),
        KEY(key1) : STRING("WORLD"),
        KEY(key2) : OBJECT{ KEY(key1):NUMBER(1)}
    };

    JSON(obj1) = OBJECT {KEY(key)  : STRING("Hello")};
    JSON(obj2) = ARRAY
    JSON(obj3) = ARRAY[STRING("A"),STRING("B"),STRING("C")];
    
    std::cout << obj0->toString() << std::endl; 
    std::cout << obj1->toString() << std::endl; 
    std::cout << obj2->toString() << std::endl; 
    std::cout << obj3->toString() << std::endl; 

PROGRAM_END

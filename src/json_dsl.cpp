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

    JSON(obj2) = TRUE

    JSON(obj3) = ARRAY
    JSON(obj4) = ARRAY[STRING("HELLO")]
    JSON(obj5) = ARRAY[STRING("HELLO"),STRING("WORD")];
    JSON(obj6) = OBJECT{};
    
    PRINT obj0, obj1, obj2, STRING("   AAAAAAAAA\n")
    PRINT obj3, obj4
    PRINT obj5
    PRINT obj6

PROGRAM_END

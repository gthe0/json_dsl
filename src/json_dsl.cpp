#include <JsonLang.hpp>

PROGRAM_BEGIN


    JSON(obj0) = OBJECT {
        KEY(key)  : STRING("Hello"),
        KEY(key1) : STRING("WORLD"),
        KEY(key2) : OBJECT{ KEY(key1):NUMBER(2)}
    }

    JSON(obj1) = OBJECT {KEY(key)  : STRING("Hello")}

    JSON(obj2) = TRUE
    JSON(obj3) = ARRAY
    JSON(obj4) = ARRAY[STRING("HELLO")]
    JSON(obj5) = ARRAY[STRING("HELLO"),STRING("WORD")];
    JSON(obj6) = OBJECT{};
    JSON(obj7) = NUMBER(10.2)

    JSON(obj8) = NULL
    PRINT obj0, obj1, obj2, STRING("   AAAAAAAAA\n"), obj0["key2"]["key1"]* obj7, STRING("   AAAAAAAAA\n")
    PRINT obj3, obj4, HAS_KEY(obj0, "key2")
    PRINT obj5, STRING("\n\n")
    PRINT obj6
    PRINT STRING("\n\n"), obj8

    PRINT STRING("\n"), obj5, STRING("\n\n")

    ERASE obj5[1]

    PRINT obj5, STRING("\n\n")


PROGRAM_END

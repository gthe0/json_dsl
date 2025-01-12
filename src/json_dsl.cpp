#include <JsonLang.hpp>

PROGRAM_BEGIN

    JSON(obj0) = OBJECT {
        KEY(key)  : STRING("Hello"),
        KEY(key1) : STRING("WORLD"),
        KEY(key2) : OBJECT{ KEY(key1):NUMBER(2), KEY(key2):NUMBER(2), KEY(null):NULL}
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

    PRINT TYPE_OF(NULL)
    PRINT NULL
    PRINT SIZE_OF(obj0["key2"])

    PRINT STRING("\n"), obj5, STRING("\n\n")

    ERASE obj5[1]

    ERASE obj0["key2"]["key1"]

    SET obj0["key2"]["key1"] ASSIGN NUMBER(4)
    SET obj5 APPEND NUMBER(4), NUMBER(5), NUMBER(5), obj5, obj5, NUMBER(5)
    JSON(array) = OBJECT{ KEY(key) : ARRAY[NUMBER(10)]}

    PRINT array, STRING("\n\n")

    SET array["key"] APPEND NUMBER(4), NUMBER(5), NUMBER(5),obj5
    PRINT array, STRING("\n\n")
    PRINT HAS_KEY(array, "key"), STRING("\n\n")
    SET array["key"][4] APPEND NUMBER(4), NUMBER(5), NUMBER(5), obj5, obj5, NUMBER(5)
    
    PRINT array, STRING("\n\n")


    PRINT obj5, STRING("\n\n")
    PRINT obj0, STRING("\n")

PROGRAM_END

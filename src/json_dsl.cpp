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
    JSON(obj7) = NUMBER(10.2);

    PRINT obj0, obj1, obj2, STRING("   AAAAAAAAA\n")
    PRINT obj3, obj4
    PRINT obj5
    PRINT obj6

    PRINT obj5[1], obj0["key2"], IS_EMPTY(obj0), IS_EMPTY(obj6), obj7 * obj0["key2"]["key1"], STRING("   "), obj7


PROGRAM_END

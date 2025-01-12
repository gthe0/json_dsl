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

    SET obj0["key2"]["key3"] ASSIGN NUMBER(2)
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
    
    PRINT array, STRING("\n\n"), NULL

    JSON(obj22) = ARRAY[NULL,NUMBER(1)] + ARRAY[NUMBER(1),NULL, STRING("HELLO WORLD")]
    ERASE obj22[4]

    PRINT obj5, STRING("\n\n")
    PRINT obj0, STRING("\n")
    PRINT SIZE_OF(obj0), STRING("\n")
    PRINT SIZE_OF(obj5), STRING("\n")
    PRINT obj22, STRING("\n")
    PRINT SIZE_OF(obj22) + SIZE_OF(obj5), STRING("\n")


    //define emptyObj json with empty object 
JSON(emptyObj) = OBJECT{} 
//define emptyArray json with empty array 
JSON(emptyArray) = ARRAY 

//define book json with an object containing data for a book 
JSON(book) = OBJECT { 
KEY(title) : STRING("Gone Girl"), 
KEY(published) : NUMBER(2012), 
KEY(type) : STRING("Thriller"), 
KEY(author) : OBJECT{ 
KEY(firstname) : STRING("GILLIAN"), 
KEY(sirname) : STRING("FLYNN"), 
KEY(age) : NUMBER(45) 
} 
} 
//define week_temperatures json with an array of numbers 
JSON(week_temperatures) = ARRAY [ 
NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20), 
NUMBER(19), NUMBER(18.5), NUMBER(19) 
] 
//define students json with an array of objects representing students 
JSON(students) = ARRAY [ 
OBJECT{ KEY(name): STRING("Nikos Nikolaou"), KEY(id) : NUMBER(4444),
    KEY(grades) : ARRAY[ 
    OBJECT { KEY(hy100) : NUMBER(7.5) }, 
    OBJECT { KEY(hy150) : NUMBER(8) } 
] 
} 
] 

//change 3rd day temperature from 19 to 22 
SET week_temperatures[2] ASSIGN NUMBER(22) 
//add email address for 1st student 
SET students[0]["email"] ASSIGN STRING("csd444@csd.uoc.gr") 
//assign new object in emptyObj json 
SET emptyObj ASSIGN OBJECT { 
KEY(a) : STRING("alpha") 
} 

//appends values 23, 22, 20 to the end of the temperature array 
SET week_temperatures APPEND NUMBER(23), NUMBER(22), NUMBER(20) 
//appends a grade for course hy255 
SET students[0]["grades"] APPEND OBJECT { KEY(hy255) : NUMBER(9) } 


PRINT book["title"] //prints:Gone Girl 
PRINT book 
PRINT book["author"] //prints:{firstname:”Gillian”,sirname:“Flynn”,age: 45} 
//prints: the whole json for book 
PRINT HAS_KEY(book, "author") //prints: true 
//prints: Book has key author? True 
PRINT STRING("Book has key author? "), HAS_KEY(book, "author") 

PRINT book, STRING("\n")

ERASE book["author"]["age"] //removes age from author object of book 
ERASE book["type"] //removes type of book 
ERASE book //removes all book data, now book is an empty object 


JSON(hy352_nik) = OBJECT{ KEY(exam):NUMBER(7), KEY(project):NUMBER(8) } 
JSON(students1) = ARRAY [ 
OBJECT{ 
KEY(name) : STRING("Nikos ") + STRING("Nikolaou"), 
KEY(id) : NUMBER(4444), 
KEY(grades) : ARRAY[ 
OBJECT { 
KEY(hy352): 
hy352_nik["exam"] * NUMBER(0.75) + hy352_nik["project"] * NUMBER(0.25) 
}]} 
]

PRINT students, STRING("\n")
PRINT students1, STRING("\n")
PRINT hy352_nik, STRING("\n")
PRINT book, STRING("\n")
PRINT week_temperatures, STRING("\n")
PRINT STRING("\nAAAAAAAA\n")

PRINT week_temperatures[0] + week_temperatures[1], STRING("\n")
PRINT week_temperatures[0] - week_temperatures[1], STRING("\n")
PRINT week_temperatures[0] % week_temperatures[1], STRING("\n")
PRINT week_temperatures[0] * week_temperatures[1], STRING("\n")
PRINT week_temperatures[0] / week_temperatures[1], STRING("\n")
PRINT week_temperatures[0] > week_temperatures[1], STRING("\n")
PRINT week_temperatures[0] < week_temperatures[1], STRING("\n")
PRINT week_temperatures[0] < week_temperatures[1], STRING("\n")
PRINT week_temperatures[0] >= week_temperatures[1], STRING("\n")
PRINT week_temperatures[0] <= week_temperatures[1], STRING("\n\n")

PRINT students[0]["grades"][1]["hy150"] + students[0]["grades"][0]["hy100"], STRING("\n")
PRINT students[0]["grades"][1]["hy150"] - students[0]["grades"][0]["hy100"], STRING("\n")
PRINT students[0]["grades"][1]["hy150"] % students[0]["grades"][0]["hy100"], STRING("\n")
PRINT students[0]["grades"][1]["hy150"] * students[0]["grades"][0]["hy100"], STRING("\n")
PRINT students[0]["grades"][1]["hy150"] / students[0]["grades"][0]["hy100"], STRING("\n")
PRINT students[0]["grades"][1]["hy150"] > students[0]["grades"][0]["hy100"], STRING("\n")
PRINT students[0]["grades"][1]["hy150"] < students[0]["grades"][0]["hy100"], STRING("\n")
PRINT students[0]["grades"][1]["hy150"] < students[0]["grades"][0]["hy100"], STRING("\n")
PRINT students[0]["grades"][1]["hy150"] >= students[0]["grades"][0]["hy100"], STRING("\n")
PRINT students[0]["grades"][1]["hy150"] <= students[0]["grades"][0]["hy100"], STRING("\n\n")

PRINT IS_EMPTY(NULL) && IS_EMPTY(week_temperatures) && IS_EMPTY(students), STRING("\n")
PRINT !IS_EMPTY(NULL) && !IS_EMPTY(week_temperatures) && !IS_EMPTY(students), STRING("\n")
PRINT IS_EMPTY(NULL) || IS_EMPTY(week_temperatures) && IS_EMPTY(students), STRING("\n")
PRINT IS_EMPTY(NULL) || IS_EMPTY(week_temperatures) || IS_EMPTY(students), STRING("\n")
PRINT !IS_EMPTY(NULL) || IS_EMPTY(week_temperatures) || IS_EMPTY(students), STRING("\n")

PRINT STRING("HELLO ") + STRING("WORLD!\n")
PRINT NUMBER(1) + NUMBER(2)
PRINT week_temperatures + students
PRINT week_temperatures + students
PRINT obj1 + students[0]["grades"][0]

PROGRAM_END

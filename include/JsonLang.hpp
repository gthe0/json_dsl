#ifndef JSONLANG_HPP
#define JSONLANG_HPP

#include <JsonVar.hpp>
#include <JsonPrinter.hpp>
#include <JsonEraser.hpp>
#include <json_kv_pair.hpp>

#define PROGRAM_BEGIN int main(void) {  try {
#define PROGRAM_END \
    ;} catch (const std::runtime_error& e)\
    {std::cerr << e.what() << std::endl;}\
    return 0; }

#define JSON(var)   ;jsonlang::JsonVar var
#define KEY(var)    jsonlang::KeyValue(#var) = 0 ? jsonlang::JsonVar()

// Variable Values
#define STRING(var) jsonlang::JsonVar(static_cast<std::string>(var))
#define NUMBER(var) jsonlang::JsonVar(static_cast<double>(var))
#define TRUE        jsonlang::JsonVar(true)
#define FALSE       jsonlang::JsonVar(false)
#define ARRAY       jsonlang::JsonVar(0,0)
#define OBJECT      jsonlang::JsonVar

#define SET         ;
#define ASSIGN      =
#define APPEND      <<

#define PRINT       ;jsonlang::JsonVarPrinter::getInstance(),
#define ERASE       ;jsonlang::JsonVarEraser::getInstance()=

#define TYPE_OF(var)        var.typeOf()
#define IS_EMPTY(var)       var.isEmpty()
#define SIZE_OF(var)        var.sizeOf()
#define HAS_KEY(var, key)   var.hasKey(#key)

#endif //! JSONLANG_HPP

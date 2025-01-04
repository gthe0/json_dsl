#ifndef JSONLANG_HPP
#define JSONLANG_HPP

#include <JsonVar.hpp>
#include <JsonPrinter.hpp>
#include <json_kv_pair.hpp>

#define PROGRAM_BEGIN int main(void) {
#define PROGRAM_END \
    ;return 0; }

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

#define PRINT       ;jsonlang::JsonVarPrinter(),

#endif //! JSONLANG_HPP

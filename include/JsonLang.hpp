#ifndef JSONLANG_HPP
#define JSONLANG_HPP

#include <JsonVar.hpp>
#include <json_kv_pair.hpp>

#if 0 
#include <JsonDSL.hpp>

#define PROGRAM_BEGIN int main(void) {
#define PROGRAM_END \
    ;return 0; }

#define JSON(var)   ;jsonlang::JsonVariable* var
#define KEY(var)    jsonlang::JsonKey(#var) = 0 ? 0

// Variable Values
#define STRING(var) new jsonlang::JsonString(var)
#define NUMBER(var) new jsonlang::JsonNumber(var)
#define TRUE        new jsonlang::JsonBoolean(true)
#define FALSE       new jsonlang::JsonBoolean(false)
#define OBJECT      new jsonlang::JsonObject
#define ARRAY           &jsonlang::createJsonArray()

// Macros that call members
#define HAS_KEY (var,key)   var == NULL ? new jsonlang::JsonBoolean(false) :jsonlang::JsonBoolean(var->hasKey(key))
#define IS_EMPTY(var)       var == NULL ? new jsonlang::JsonBoolean(false) :jsonlang::JsonBoolean(var->isEmpty())
#define SIZE_OF (var)       var == NULL ? NUMBER(1)      :NUMBER(var->sizeOf())
#define TYPE_OF (var)       var == NULL ? STRING("null") :STRING(var->typeOf())
#endif

#define PROGRAM_BEGIN int main(void) {
#define PROGRAM_END \
    ;return 0; }

#define JSON(var)   ;jsonlang::JsonVar var
#define KEY(var)    jsonlang::KeyValue(#var) = 0 ? 0

// Variable Values
#define STRING(var) jsonlang::JsonVar(var)
#define NUMBER(var) jsonlang::JsonVar(var)
#define TRUE        jsonlang::JsonVar(true)
#define FALSE       jsonlang::JsonVar(false)
#define ARRAY       jsonlang::JsonVar()
#define OBJECT      jsonlang::JsonVar

#endif //! JSONLANG_HPP

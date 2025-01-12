# JSON_DSL
A simple DSL used to process and create JSON objects, written using the C preprocessor.

# COMPILATION

## USING MAKE
Having make installed in your system, type:

` make`

or

` make compile`

The executable will be located inside the bin directory.

## USING CMAKE
Having CMAKE installed in your system, type:

` cmake -Bbuild && cmake --build build`

The executable will be located inside the bin directory.

> [!NOTE]  
> SIZE_OF and IS_EMPTY currently count the NULL value. We added an implementation where we do not.
> If you want to compile it using this, add the -DTA_WAY compiler option

# USAGE

Include the JsonLang.hpp file header in your program.

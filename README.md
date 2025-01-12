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
> SIZE_OF and IS_EMPTY currently do not count the NULL value due to an email that a TA sent. We added an implementation where we do, just in case.
> If you want to compile this implementation, add the following compilation option -DOTHER_WAY 

# USAGE

Include the JsonLang.hpp file header in your program.

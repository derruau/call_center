/* 
========================================== ARG_TYPES.C ==========================================
This file is where all the types used in the Argument Parser are defined.

They are not defined in their respective relevant files because that would create circular
references.

The types are organised by the file would normally be defined in.

TOKENIZER types:
    The idea behind all those types is to have a single struct (Token) that can contain all data
    types and differenciate between a FLAG and a VALUE.
        - A FLAG is a strings arguments that start matches the flag type definition (see Tokenizer.c) 
        - A VALUE is a string argument that matches any type definition that is not a FLAG
    
    The Token type is structured like this:
    {
        TYPE: FLAG or VALUE
        DATA: FLAG_DATA or VALUE_DATA
    }

    The _value_type enum defines all possible VALUE types. It is very important that the enum's 
    value is a power of two! This is because when the Lexer checks the type of each Token against
    the syntax, it performs a bitwise AND between the Token type and the allowed types of the
    parameter (which in turn is the bitwise OR or all possible types).

    The _token_type enum defines if a Token is a FLAG or a VALUE.

    The _s_flag and _s_value structs contain the actual data in a Token. You NEED to have the
    VALUE's data type inside _s_value because in order to store any type of data inside the struct
    you have to store it as a void pointer which needs to be casted back into it's type when 
    reading it.

    The _token_data type is a union type that either stores a _s_flag or a _s_value.

    Remarks:
        The design can be SIMPLIFIED by removing the differenciation between FLAG and VALUE 
        and have a FLAG just be a _value_type thus removing the need for _token_data and
        _s_value but I currently don't have the time to refactor the code.


ARGS types:
    The Arguments struct is the structure the string arguments will be parsed into.

LEXER types:
    Theses types aim to define a Syntax struct which contains all possible Rules of the syntax.

    A Rule is a structure that contains a FULL_NAME, (which also potentially has an abreviated name)
    a NUMBER_OF_VALUES following it and a list containing the VALUEs_TYPES.
    For example: If I want to add the following argument to my program:
                --[FULL_NAME] [VALUE_1]   [VALUE_2]     [VALUE_3]
                                 int     float or int    duration
    I create a Rule struct with FULL_NAME as the full_name, 3 as the NUMBER_OF_VALUES
    and {INT, INT | FLOAT, DURATION} as the VALUEs_TYPES

    A Rule also needs a Callback which is a function that takes in an Argument struct,
    and the Tokens corresponding to it's VALUES and puts the Tokens data into the Argument struct.
========================================== ARG_TYPES.C ==========================================
*/

#include <time.h>

//================ tokenizer.c types ================

typedef enum _e_value_type {
    INT = 0b00001,
    FLOAT = 0b00010,
    DURATION = 0b00100,
    DURATION_UNIT = 0b01000,
    STRING = 0b10000,
} _value_type;

typedef enum e_token_type {
    FLAG,
    VALUE
} _token_type;

struct _s_flag {
    char *name;
};

struct _s_value {
    void *data;
    _value_type type;
};

typedef union _u_token {
    struct _s_flag* f;
    struct _s_value* v;
} _token_data;

typedef struct s_token {
    _token_type type;
    _token_data data;
} Token;

//================ args.c types ================

typedef struct s_arguments{
    int help;
    int version;
    float lambda;
    int operators;
    int number_of_days;

    // Corresponds to the -d argument
    time_t minsrv;
    time_t maxsrv;

    // Corresponds to the -s argument
    time_t shift_opening;
    time_t shift_closing;

    char *path;
} Arguments;

//================ lexer.c types ================

typedef void (*lexer_callback)(Arguments *a, Token **t); 

typedef struct {
    char abv;
    int has_abv;
    char *full_name;
    
    //Callback to when there is a match in tokens
    lexer_callback cb;

    // Number of value tokens after the flag
    int param_number;
    // Type of each Value Parameter. A parameter can be of multiple types,
    // so each int is the Bitwise-OR of all the types he can be
    // For example: if the parameter can be a FLOAT or an INT the Value will be
    // equal to FLOAT | INT
    int param_type[];
} Rule;

typedef struct {
    int max_size;
    int current_size;
    // A hash table would be better because that would mean
    // instant access time but with small syntax size it's fine.
    Rule **s;
} Syntax;
#ifndef TOKEN_FLAG
#define TOKEN_FLAG



enum class State {
    INVALID,
    START,
    IDENT,
    NUMBER,
    SYMBOL,
    LABEL
};


enum class token_type
 {
    IDENT,
    LABEL,
    INT,
    INPUT,
    OUTPUT,
    GOTO,
    IF,
    THEN,
    EQUAL,
    SET,
    PLUS,
    LESS_THAN,
    INVALID,
    END
};

#endif
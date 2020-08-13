#ifndef MAIN_FLAGS
#define MAIN_FLAGS
enum MAIN_FLAGS
{
    NOTHING = 0,
    UNARY,
    BINARY,
    MULTI,
    META,
    NUM,
    VAR,
    CONST
};

enum UNARY_OPERATIONS
{
    FACT = 1,
    SIN,
    COS,
    TAN,
    CSC,
    SEC,
    COT,
    LOG,
    LN
};

enum BINARY_OPERATIONS
{
    ADD = 1,
    SUB,
    MUL,
    DIV,
    POW,
    PERM,
    COMB,
    LOG_
};

enum MULTIPLE
{
    MEAN_SD = 1
};

enum META_DATA
{
    SPACE = 0,
    OPEN_BRAC,
    CLOSE_BRAC
};

enum CONSTANTS
{
    PI = 1,
    EULER
};
#endif

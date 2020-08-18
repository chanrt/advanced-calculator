#ifndef FLAGS
#define FLAGS
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
    ASIN,
    ACOS,
    ATAN,
    LOG,
    LN,
    SQRT,
    CBRT,
    RECI
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
    LOG_,
    MOD,
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
    PI = 0,
    EU,
    GR,

    SOL,
    H,
    HC,
    G,

    EM,
    PM,
    NM,
    BR,
    FS,
    HE,
    R,

    M_PER,
    E_PER,
    Z,
    KC,
    EC,
    BM,
    NUC_M,
    VK,

    AMU,
    AN,
    KB,
    F,
    C1,
    C2,
    UG,
    SB,
    WD,
};
#endif

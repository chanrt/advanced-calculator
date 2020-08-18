#define SHOW_INIT_FLAG 1

#include <iostream>
#include "flags.cpp"
#include "reader.cpp"

Reader initializeUnary(Reader reader)
{
    reader.addEntity("~", UNARY, RECI);
    reader.addEntity("!", UNARY, FACT);
    reader.addEntity("sqrt", UNARY, SQRT);
    reader.addEntity("cbrt", UNARY, CBRT);
    reader.addEntity("sin", UNARY, SIN);
    reader.addEntity("cos", UNARY, COS);
    reader.addEntity("tan", UNARY, TAN);
    reader.addEntity("csc", UNARY, CSC);
    reader.addEntity("sec", UNARY, SEC);
    reader.addEntity("cot", UNARY, COT);
    reader.addEntity("asin", UNARY, ASIN);
    reader.addEntity("acos", UNARY, ACOS);
    reader.addEntity("atan", UNARY, ATAN);
    reader.addEntity("log", UNARY, LOG);
    reader.addEntity("ln", UNARY, LN);

    return reader;
}

Reader initializeBinary(Reader reader)
{
    reader.addEntity("+", BINARY, ADD);
    reader.addEntity("-", BINARY, SUB);
    reader.addEntity("*", BINARY, MUL);
    reader.addEntity("/", BINARY, DIV);
    reader.addEntity("^", BINARY, POW);
    reader.addEntity("%", BINARY, MOD);
    reader.addEntity("P", BINARY, PERM);
    reader.addEntity("C", BINARY, COMB);
    reader.addEntity("log_", BINARY, LOG_);

    return reader;
}

Reader initializeMulti(Reader reader)
{
    reader.addEntity("mean_sd", MULTI, MEAN_SD);

    return reader;
}

Reader initializeMeta(Reader reader)
{
    reader.addEntity("(", META, OPEN_BRAC);
    reader.addEntity(")", META, CLOSE_BRAC);

    return reader;
}

Reader initializeConstants(Reader reader)
{
    // math constants
    reader.addEntity("#pi", CONST, PI);
    reader.addEntity("#eu", CONST, EU);
    reader.addEntity("#gr", CONST, GR);

    // universal constants
    reader.addEntity("#c", CONST, SOL);
    reader.addEntity("#h", CONST, H);
    reader.addEntity("#rh", CONST, HC);
    reader.addEntity("#G", CONST, G);

    // atomic and nuclear constants
    reader.addEntity("#em", CONST, EM);
    reader.addEntity("#pm", CONST, PM);
    reader.addEntity("#nm", CONST, NM);
    reader.addEntity("#br", CONST, BR);
    reader.addEntity("#fs", CONST, FS);
    reader.addEntity("#he", CONST, HE);
    reader.addEntity("#r", CONST, R);

    // physio-chemical constants
    reader.addEntity("#fr", CONST, C1);
    reader.addEntity("#sr", CONST, C2);
    reader.addEntity("#amu", CONST, AMU);
    reader.addEntity("#an", CONST, AN);
    reader.addEntity("#kb", CONST, KB);
    reader.addEntity("#f", CONST, F);
    reader.addEntity("#ug", CONST, UG);
    reader.addEntity("#sb", CONST, SB);
    reader.addEntity("#wd", CONST, WD);

    // electromagnetic constants
    reader.addEntity("#m_per", CONST, M_PER);
    reader.addEntity("#e_per", CONST, E_PER);
    reader.addEntity("#z", CONST, Z);
    reader.addEntity("#kc", CONST, KC);
    reader.addEntity("#ec", CONST, EC);
    reader.addEntity("#bm", CONST, BM);
    reader.addEntity("#nuc_m", CONST, NUC_M);
    reader.addEntity("#vk", CONST, VK);
    
    return reader;
}

Reader initializeReader(Reader reader)
{
    reader.clearInternalData();
    reader.clearExternalData();
    reader.setDebugReader(false);

    reader = initializeBinary(reader);
    reader = initializeUnary(reader);
    reader = initializeConstants(reader);
    reader = initializeMulti(reader);
    reader = initializeMeta(reader);

    if(SHOW_INIT_FLAG)
    {
        cout << "The following characters and words are recognized: ";
        reader.printInfo();
        cout << endl;
    }
    return reader;
}
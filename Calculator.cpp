enum COMMANDS
{
    EVAL = 1
};

#include <iostream>
#include <string>

#include "flags.cpp"
#include "Reader.cpp"
Reader reader;

#include "Evaluater.cpp"
Evaluater evaluater;

using namespace std;
int current_command;

void initializeFunctions()
{
    reader.clearInternalData();
    reader.clearExternalData();
    reader.setDebugReader(false);

    evaluater.clearData();
    evaluater.setDegreeMode();
    evaluater.setDebugEval(false);

    reader.addEntity("+", BINARY, ADD);
    reader.addEntity("-", BINARY, SUB);
    reader.addEntity("*", BINARY, MUL);
    reader.addEntity("/", BINARY, DIV);
    reader.addEntity("^", BINARY, POW);
    reader.addEntity("P", BINARY, PERM);
    reader.addEntity("C", BINARY, COMB);
    reader.addEntity("log_", BINARY, LOG_);

    reader.addEntity("!", UNARY, FACT);
    reader.addEntity("sin", UNARY, SIN);
    reader.addEntity("cos", UNARY, COS);
    reader.addEntity("tan", UNARY, TAN);
    reader.addEntity("csc", UNARY, CSC);
    reader.addEntity("sec", UNARY, SEC);
    reader.addEntity("cot", UNARY, COT);
    reader.addEntity("log", UNARY, LOG);
    reader.addEntity("ln", UNARY, LN);

    reader.addEntity("mean_sd", MULTI, MEAN_SD);

    reader.addEntity("(", META, OPEN_BRAC);
    reader.addEntity(")", META, CLOSE_BRAC);

    cout << "----> Advanced Calculator <----" << endl;
    cout << "The following characters and words are recognized: ";
    reader.printInfo();
    cout << endl;
}

void reinit_eval()
{
    reader.clearExternalData();
    evaluater.clearData();
}

bool isNotExit(string prompt)
{
    return (prompt != "exit");
}

bool atFirst(string prompt, string command)
{
    if (command.size() > prompt.size())
        return false;

    for (int i = 0; i < command.size(); i++)
    {
        if (prompt[i] != command[i])
            return false;
    }
    return true;
}

void checkCommand(string prompt)
{
    if (atFirst(prompt, "eval"))
        current_command = EVAL;
    else if (atFirst(prompt, "radian mode"))
    {
        evaluater.setRadianMode();
        cout << "Mode changed to Radians" << endl;
    }
    else if (atFirst(prompt, "degree mode"))
    {
        evaluater.setDegreeMode();
        cout << "Mode changed to Degrees" << endl;
    }
    else if (atFirst(prompt, "debug eval"))
    {
        evaluater.setDebugEval(true);
        cout << "Debugging eval" << endl;
    }
    else if (atFirst(prompt, "debug reader"))
    {
        reader.setDebugReader(true);
        cout << "Debugging reader" << endl;
    }
}

int main()
{
    initializeFunctions();
    current_command = EVAL;
    string prompt = "";

    while (isNotExit(prompt))
    {
        cout << "> ";
        getline(cin, prompt);
        checkCommand(prompt);

        if (current_command == EVAL)
        {
            if (atFirst(prompt, "eval"))
                reader.parse(prompt, 4);
            else
                reader.parse(prompt, 0);

            if (reader.getEquationSize() > 0)
            {
                evaluater.initialize(reader.getEquation(), reader.getFlags());
                cout << " = " << evaluater.evaluate(0, reader.getEquationSize()) << endl;
                reinit_eval();
            }
        }
    }
}
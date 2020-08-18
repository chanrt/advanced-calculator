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

#include "initializer.cpp"
#include "communicator.cpp"

using namespace std;
int current_command;

void reinit_eval()
{
    reader.clearExternalData();
    evaluater.clearData();
    show_eval_equals = true;
    show_eval_result = true;
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
    cout << "----> Advanced Calculator <----" << endl;
    reader = initializeReader(reader);

    current_command = EVAL;
    string prompt = "";
    double result;

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
                result = evaluater.evaluate(0, reader.getEquationSize());

                if(show_eval_equals)
                    cout << " = ";
                if(show_eval_result)
                    cout << result;
                    
                cout << endl;
                reinit_eval();
            }
        }
    }
}
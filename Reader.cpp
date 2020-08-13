#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "flags.cpp"
using namespace std;

class Reader
{
private:
    // based on prompt
    vector<int> flags;
    vector<double> equation;
    int external_registry_size;

    // internal data
    vector<string> identifiers_info;
    vector<int> flags_info;
    vector<double> equation_info;
    int internal_registry_size;

    // operations parameters
    bool inside_num, after_decimal_point;
    int place_value;
    double new_num;
    bool debug_reader;

    // operational functions

    void initializeForNums()
    {
        inside_num = false;
        after_decimal_point = false;
        new_num = 0.0;
        place_value = 0;
    }

    void pushNum(double num)
    {
        equation.push_back(num);
        flags.push_back(NUM);
        external_registry_size++;

        if (debug_reader)
            cout << "New number pushed: " << num << endl;
    }

    void pushData(int j)
    {
        equation.push_back(equation_info[j]);
        flags.push_back(flags_info[j]);
        external_registry_size++;

        if (debug_reader)
            cout << "New data pushed: " << identifiers_info[j] << endl;
    }

    void pushVar(char c)
    {
        equation.push_back(c - 'a' + 1);
        flags.push_back(VAR);
        external_registry_size++;

        if (debug_reader)
            cout << "New variable pushed: " << c << endl;
    }

    bool isSame(string prompt, int location, string name)
    {
        if (prompt.size() - location < name.size())
            return false;

        int i, j;
        for (i = location, j = 0; j < name.size(); i++, j++)
        {
            if (prompt[i] != name[j])
                return false;
        }

        //if(isAlpha(prompt[location-1]) || isAlpha(prompt[location+name.size()+1])) return false;

        if (debug_reader)
            cout << name << " found at location " << location << endl;
        return true;
    }

    // helper functions
    bool isNum(char c)
    {
        return (c > 47 && c < 58);
    }

    bool isPoint(char c)
    {
        return (c == '.');
    }

    int getNum(char c)
    {
        return (c - 48);
    }

    int isAlpha(char c)
    {
        return (c > 96 && c < 123);
    }

    bool isAloneAlpha(string prompt, int location)
    {
        if (location == 0)
            return (isAlpha(prompt[location]) && !isAlpha(prompt[location + 1]));
        else if (location == prompt.size() - 1)
            return (isAlpha(prompt[location]) && !isAlpha(prompt[location - 1]));
        else
            return (isAlpha(prompt[location]) && !isAlpha(prompt[location - 1]) && !isAlpha(prompt[location + 1]));
    }

public:
    void parse(string prompt, int start)
    {
        initializeForNums();
        prompt = prompt + " ";
        for (int i = start; i < prompt.size(); i++)
        {
            if (debug_reader)
                cout << "Character encountered: " << prompt[i] << endl;

            if (!inside_num)
            {
                if (isNum(prompt[i]))
                {
                    inside_num = true;
                    new_num = getNum(prompt[i]);
                }
                else if (isPoint(prompt[i]))
                {
                    inside_num = true;
                    after_decimal_point = true;
                    place_value--;
                }
                else if (isAloneAlpha(prompt, i))
                {
                    pushVar(prompt[i]);
                }
                else
                {
                    for (int j = 0; j < identifiers_info.size(); j++)
                    {
                        if (isSame(prompt, i, identifiers_info[j]))
                        {
                            pushData(j);
                            i = i + identifiers_info[j].size() - 1;
                            break;
                        }
                    }
                }
            }
            else if (inside_num)
            {
                if (isNum(prompt[i]))
                {
                    if (!after_decimal_point)
                    {
                        new_num = (10 * new_num) + getNum(prompt[i]);
                    }
                    else if (after_decimal_point)
                    {
                        new_num = new_num + double(pow(10, place_value) * getNum(prompt[i]));
                        place_value--;
                    }
                }
                else if (isPoint(prompt[i]))
                {
                    after_decimal_point = true;
                    place_value--;
                }
                else if (isAloneAlpha(prompt, i))
                {
                    pushVar(prompt[i]);
                }
                else
                {
                    pushNum(new_num);
                    initializeForNums();

                    for (int j = 0; j < identifiers_info.size(); j++)
                    {
                        if (isSame(prompt, i, identifiers_info[j]))
                        {
                            pushData(j);
                            i = i + identifiers_info[j].size() - 1;
                            break;
                        }
                    }
                }
            }
        }
        if (new_num != 0.0)
            pushNum(new_num);
    }

    void clearExternalData()
    {
        external_registry_size = 0;
        flags.clear();
        equation.clear();
    }

    void clearInternalData()
    {
        internal_registry_size = 0;
        identifiers_info.clear();
        flags_info.clear();
        equation_info.clear();
    }

    void addEntity(string name, int type, int ID)
    {
        identifiers_info.push_back(name);
        flags_info.push_back(type);
        equation_info.push_back(ID);
        internal_registry_size++;
    }

    void printInfo()
    {
        if (internal_registry_size == 0)
        {
            cout << "Nothing in internal registry of reader";
            return;
        }

        cout << endl;
        for (string name : identifiers_info)
            cout << name << ", ";
        cout << endl;
    }

    void printData()
    {
        if (external_registry_size == 0)
        {
            cout << "Nothing in internal registry of reader";
            return;
        }

        for (int i = 0; i < external_registry_size; i++)
        {
            cout << " ";

            if (flags[i] == UNARY)
            {
                if (equation[i] == FACT)
                    cout << "FACT";
                else if (equation[i] == SIN)
                    cout << "SIN";
                else if (equation[i] == COS)
                    cout << "COS";
                else if (equation[i] == TAN)
                    cout << "TAN";
            }
            else if (flags[i] == BINARY)
            {
                if (equation[i] == ADD)
                    cout << "ADD";
                else if (equation[i] == SUB)
                    cout << "SUB";
                else if (equation[i] == MUL)
                    cout << "MUL";
                else if (equation[i] == DIV)
                    cout << "DIV";
                else if (equation[i] == POW)
                    cout << "POW";
            }
            else if (flags[i] == META)
            {
                if (equation[i] == OPEN_BRAC)
                    cout << "(";
                else if (equation[i] == CLOSE_BRAC)
                    cout << ")";
            }
            else if (flags[i] == NUM)
                cout << equation[i];
            else if (flags[i] == VAR)
                cout << "VAR_" << equation[i];
        }
        cout << endl;
    }

    vector<double> getEquation()
    {
        return equation;
    }

    vector<int> getFlags()
    {
        return flags;
    }

    int getEquationSize()
    {
        return external_registry_size;
    }

    void setDebugReader(bool value)
    {
        debug_reader = value;
    }
};
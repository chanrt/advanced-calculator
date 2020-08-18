#include <vector>
#include <cmath>
#include "flags.cpp"
#include "math/Math.cpp"
#include "constants.cpp"
#include "communicator.cpp"
using namespace std;

class Evaluater
{
private:
    vector<double> equation;
    vector<int> flags;
    double result;
    bool degree_mode;
    bool debug_eval;
    bool no_result;

    int numBrackets(int start, int end)
    {
        int num_brackets = 0;
        for (int i = start; i < end; i++)
        {
            if (flags[i] == META && (equation[i] == OPEN_BRAC || equation[i] == CLOSE_BRAC))
                num_brackets++;
        }
        return num_brackets;
    }

    int getOpenBracket(int start, int end)
    {
        for (int i = start; i < end; i++)
        {
            if (flags[i] == META && equation[i] == OPEN_BRAC)
                return i;
        }
        return -1;
    }

    int getCloseBracket(int start, int end)
    {
        int num_open = 1, num_close = 0;

        for (int i = start; i < end; i++)
        {
            if (flags[i] == META)
            {
                if (equation[i] == OPEN_BRAC)
                    num_open++;
                else if (equation[i] == CLOSE_BRAC)
                    num_close++;
            }
            if (num_open == num_close)
                return i;
        }
        return -1;
    }

    void makeEmpty(int start, int end)
    {
        for (int i = start; i <= end; i++)
        {
            equation[i] = 0;
            flags[i] = NOTHING;
        }
    }

    void putNum(double num, int index)
    {
        equation[index] = num;
        flags[index] = NUM;
    }

    void clearIndex(int index)
    {
        equation[index] = 0;
        flags[index] = NOTHING;
    }

    int getFirstNumToLeft(int start, int index)
    {
        for (int i = index; i >= start; i--)
        {
            if (flags[i] == NUM)
                return i;
        }
        return -1;
    }

    int getFirstNumToRight(int index, int end)
    {
        for (int i = index; i < end; i++)
        {
            if (flags[i] == NUM)
                return i;
        }
        return -1;
    }

    int getFirstNonNumToRight(int index, int end)
    {
        for (int i = index; i < end; i++)
        {
            if (flags[i] != NUM)
                return i;
        }
        return -1;
    }

    int numNums(int start, int end)
    {
        int num = 0;
        for (int i = start; i < end; i++)
        {
            if (flags[i] == NUM)
                num++;
        }
        return num;
    }

    void printVectors()
    {
        for (auto e : equation)
            cout << e << " ";
        cout << "\t";
        for (auto e : flags)
            cout << e << " ";
        cout << endl;
    }

public:
    double evaluate(int start, int end)
    {
        bool no_result = false;
        if (debug_eval)
        {
            cout << "Received vectors:" << endl;
            printVectors();
            cout << "Start: " << start << " and end: " << end << endl;
        }

        while (numBrackets(start, end) > 0)
        {
            int index1, index2;
            index1 = getOpenBracket(start, end);
            index2 = getCloseBracket(index1 + 1, end);

            result = evaluate(index1 + 1, index2);
            makeEmpty(index1, index2);
            putNum(result, index1);
        }

        // constants
        vector<int> const_index = getConstIndex();
        for (int i = 0; i < end; i++)
        {
            if (flags[i] == CONST)
            {
                for (int j = 0; j < const_index.size(); j++)
                {
                    if (equation[i] == const_index[j])
                        putNum(getConst(j), i);
                }
            }
        }

        int index1, index2;

        // unary operations
        for (int i = end - 1; i >= start; i--)
        {
            if (flags[i] == UNARY)
            {
                if (equation[i] == FACT)
                    index1 = getFirstNumToLeft(start, i);
                else
                    index2 = getFirstNumToRight(i, end);

                if (equation[i] == FACT)
                    putNum(getFact(equation[index1]), index1);
                else if (equation[i] == SIN)
                    putNum(getSin(equation[index2], degree_mode), index2);
                else if (equation[i] == COS)
                    putNum(getCos(equation[index2], degree_mode), index2);
                else if (equation[i] == TAN)
                    putNum(getTan(equation[index2], degree_mode), index2);
                else if (equation[i] == CSC)
                    putNum(1.0 / getSin(equation[index2], degree_mode), index2);
                else if (equation[i] == SEC)
                    putNum(1.0 / getCos(equation[index2], degree_mode), index2);
                else if (equation[i] == COT)
                    putNum(1.0 / getTan(equation[index2], degree_mode), index2);
                else if (equation[i] == ASIN)
                    putNum(getArcSin(equation[index2], degree_mode), index2);
                else if (equation[i] == ACOS)
                    putNum(getArcCos(equation[index2], degree_mode), index2);
                else if (equation[i] == ATAN)
                    putNum(getArcTan(equation[index2], degree_mode), index2);
                else if (equation[i] == LOG)
                    putNum(getLog(equation[index2]), index2);
                else if (equation[i] == LN)
                    putNum(getLn(equation[index2]), index2);
                else if (equation[i] == SQRT)
                    putNum(sqrt(equation[index2]), index2);
                else if (equation[i] == CBRT)
                    putNum(pow(equation[index2], 0.3333333333), index2);
                else if (equation[i] == RECI)
                    putNum(1.0 / equation[index2], index2);
                else if (equation[i] == IS_PRIME)
                {
                    no_result = true;
                    if (isPrime(equation[index2]))
                        cout << "The number " << equation[index2] << " is prime";
                    else
                        cout << "The number " << equation[index2] << " is not prime";
                }
                else if (equation[i] == PRIME_FACTORS)
                {
                    putNum(primeFactors(equation[index2]), index2);
                    cout << "Number of prime factors: ";
                }
                else if (equation[i] == PRIME_FACTORIZE)
                {
                    putNum(primeFactorize(equation[index2]), index2);
                    cout << "Number of terms: ";
                }

                clearIndex(i);
            }
        }

        if (debug_eval)
        {
            cout << "After unary operations" << endl;
            printVectors();
        }

        vector<int> bin_order;
        bin_order.push_back(LOG_);
        bin_order.push_back(MOD);
        bin_order.push_back(PERM);
        bin_order.push_back(COMB);
        bin_order.push_back(POW);
        bin_order.push_back(DIV);
        bin_order.push_back(MUL);
        bin_order.push_back(ADD);
        bin_order.push_back(SUB);

        for (int i = 0; i < bin_order.size(); i++)
        {
            for (int j = start; j < end; j++)
            {
                if (flags[j] == BINARY && equation[j] == bin_order[i])
                {
                    if (equation[j] == LOG_)
                    {
                        index1 = getFirstNumToRight(j, end);
                        index2 = getFirstNumToRight(index1 + 1, end);
                    }
                    else
                    {
                        index1 = getFirstNumToLeft(start, j);
                        index2 = getFirstNumToRight(j, end);
                    }

                    if (equation[j] == LOG_)
                        putNum(getLogBaseN(equation[index2], equation[index1]), index1);
                    else if (equation[j] == MOD)
                        putNum(int(equation[index1]) % int(equation[index2]), index1);
                    else if (equation[j] == PERM)
                        putNum(getPerm(equation[index1], equation[index2]), index1);
                    else if (equation[j] == COMB)
                        putNum(getComb(equation[index1], equation[index2]), index1);
                    else if (equation[j] == POW)
                        putNum(pow(equation[index1], equation[index2]), index1);
                    else if (equation[j] == DIV)
                        putNum(equation[index1] / equation[index2], index1);
                    else if (equation[j] == MUL)
                        putNum(equation[index1] * equation[index2], index1);
                    else if (equation[j] == ADD)
                        putNum(equation[index1] + equation[index2], index1);
                    else if (equation[j] == SUB)
                        putNum(equation[index1] - equation[index2], index1);

                    clearIndex(j);
                    clearIndex(index2);
                }
            }
        }

        for (int i = start; i < end; i++)
        {
            if (flags[i] == MULTI)
            {
                index1 = getFirstNumToRight(i, end);
                index2 = getFirstNonNumToRight(index1, end);

                if (index2 == -1)
                    index2 = end;

                if (equation[i] == LCM)
                {
                    no_result = true;
                    makeEmpty(i, getLCM(equation, flags, index1, index2));
                }
                else if (equation[i] == HCF)
                {
                    no_result = true;
                    makeEmpty(i, getHCF(equation, flags, index1, index2));
                }
                else if (equation[i] == MEAN_SD)
                {
                    no_result = true;
                    makeEmpty(i, mean_sd(equation, flags, index1, index2));
                }
            }
        }

        if (debug_eval)
        {
            cout << "After binary operations" << endl;
            printVectors();
        }

        if (numNums(start, end) == 1 && !no_result)
            return equation[getFirstNumToRight(start, end)];
        else if (!no_result)
            printf("Error in evaluation");

        show_eval_equals = show_eval_result = !no_result;

        return 0;
    }

    void
    initialize(vector<double> equations_array, vector<int> flags_array)
    {
        equation = equations_array;
        flags = flags_array;
    }

    void clearData()
    {
        equation.clear();
        flags.clear();
    }

    void setDegreeMode()
    {
        degree_mode = true;
    }

    void setRadianMode()
    {
        degree_mode = false;
    }

    void setDebugEval(bool value)
    {
        debug_eval = value;
    }
};
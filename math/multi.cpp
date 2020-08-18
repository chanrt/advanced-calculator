#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
#include "../flags.cpp"

using namespace std;

int mean_sd(vector<double> equation, vector<int> flags, int index1, int index2)
{
    float sum = 0.0;
    int nums = 0;
    int last_num_index;

    for (int j = index1; j < index2; j++)
    {
        if (flags[j] == NUM)
        {
            sum += equation[j];
            nums++;
            last_num_index = j;
        }
    }

    float mean = sum / nums;
    sum = 0.0;

    for (int j = index1; j <= last_num_index; j++)
    {
        if (flags[j] == NUM)
            sum += (mean - equation[j]) * (mean - equation[j]);
    }

    printf("Mean: %f and Standard deviation: %f", mean, sqrt(sum / nums));
    return last_num_index;
}

int getLCM(vector<double> equation, vector<int> flags, int index1, int index2)
{
    int max = INT_MIN;
    int last_num_index = index1;

    vector<int> nums;

    for (int j = index1; j < index2; j++)
    {
        if (flags[j] == NUM)
        {
            if(equation[j] > max)
                max = equation[j];

            nums.push_back(equation[j]);
            last_num_index = j;
        }
    }

    int lcm = max;
    bool all_divisible = false;

    while(!all_divisible)
    {
        all_divisible = true;

        for(int i = 0; i < nums.size(); i++)
        {
            if(lcm % nums[i] != 0)
            {
                lcm = lcm + max;
                all_divisible = false;
                break;
            }
        }
    }
    cout << "The LCM of these numbers is: " << lcm;
    return last_num_index;
}

int getHCF(vector<double> equation, vector<int> flags, int index1, int index2)
{
    int min = INT_MAX;
    int last_num_index = index1;

    vector<int> nums;

    for (int j = index1; j < index2; j++)
    {
        if (flags[j] == NUM)
        {
            if(equation[j] < min)
                min = equation[j];

            nums.push_back(equation[j]);
            last_num_index = j;
        }
    }

    int hcf = min;
    bool all_divisible = false;

    while(!all_divisible && hcf > 1)
    {
        all_divisible = true;

        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] % hcf != 0)
            {
                hcf--;
                all_divisible = false;
                break;
            }
        }
    }

    cout << "The HCF of these numbers is: " << hcf;
    return last_num_index;
}
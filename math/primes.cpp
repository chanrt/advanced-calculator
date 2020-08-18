#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int num)
{
    num = abs(num);
    int limit = sqrt(num);

    if(num == 0 || num == 1)
        return false;
    else if(num == 2 || num == 3)
        return true;
    
    for(int i = 2; i <= limit; i++)
    {
        if(num % i == 0)
            return false;
    }
    return true;
}

int primeFactors(int num)
{
    num = abs(num);
    int limit = (num / 2) + 1;
    int num_factors = 0;

    cout << "Prime factors of " << num << ": " << endl;
    if(num == 0 || num == 1)
    {
        cout << "None";
        return 0;
    }

    for(int i = 2; i < limit; i++)
    {
        if(num % i == 0 && isPrime(i))
        {
            cout << i << " ";
            num_factors++;
        }
    }
    cout << endl;
    return num_factors;
}

int primeFactorize(int num)
{
    num = abs(num);
    int limit = (num / 2) + 1;
    int num_factors = 0;

    cout << "Prime factorization of " << num << " is: " << endl;
    if(num == 0 || num == 1)
    {
        cout << "None";
        return 0;
    }

    int i = 2;
    while(i <= num)
    {
        if(isPrime(i))
        {
            while(num % i == 0)
            {
                cout << i << "*";
                num_factors++;
                num = num / i;
            }
        }
        i++;
    }
    cout << "1" << endl;
    return num_factors;
}
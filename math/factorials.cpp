long long getFact(int num)
{
    if (num == 0 || num == 1)
        return 1;

    long long answer = num;
    for (int i = num - 1; i > 0; i--)
    {
        answer = answer * i;
    }
    return answer;
}

double getPerm(int n, int r)
{
    return (getFact(n)/getFact(n-r));
}

double getComb(int n, int r)
{
    return (getPerm(n,r)/getFact(r));
}
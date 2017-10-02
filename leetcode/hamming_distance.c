int hammingDistance(int x, int y)
{
    int d = 0, xor = x ^ y;

    while(xor != 0)
    {
        ++d;
        xor &= xor - 1;
    }

    return d;
}

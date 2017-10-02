#include <stdbool.h>

bool judgeCircle(char *moves)
{
    int x = 0, y = 0;
    char c;

    while((c = *moves))
    {
        switch (c)
        {
        case 'R':
            ++x;
            break;
        case 'L':
            --x;
            break;
        case 'U':
            ++y;
            break;
        case 'D':
            --y;
            break;
        default:
            break;
        }
        ++moves;
    }

    return x == 0 && y == 0;
}

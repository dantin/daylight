#include <stdio.h>

#define SIZE 100000
#define LINE  50
#define SYMBOL 255
#define TIMES 6

void init_symbol_table(char *symboles);

int main(int argc, char *argv[])
{
    int i, j, n, times;
    char line[LINE];
    char symbolTable[SYMBOL];
    int phones[SIZE];

    init_symbol_table(symbolTable);

    scanf("%d", &n);
    for(i = 0; i < n; ++i)
    {
        scanf("%s", &line);
        phones[i] = 0;

        times = TIMES;
        for(j = 0; j < LINE; ++j)
        {
            if((line[j] >= 'A' && line[j] <= 'Z') || (line[j] >= '0' && line[j] <= '9'))
            {
                phones[i] = phones[i] * 10 + symbolTable[line[j]];
                --times;
                if(times < 0)
                    break;
            }
        }
    }

    for(i = 0; i < n; ++i)
    {
        printf("%d\n", phones[i]);
    }

    return 0;
}

/**
 * Initialize symbol table.
 *
 *   symbols: pointer to the symbol table
 */
void init_symbol_table(char *symbols)
{
    symbols['0'] = 0;
    symbols['1'] = 1;
    symbols['A'] = symbols['B'] = symbols['C'] = symbols['2'] = 2;
    symbols['D'] = symbols['E'] = symbols['F'] = symbols['3'] = 3;
    symbols['G'] = symbols['H'] = symbols['I'] = symbols['4'] = 4;
    symbols['J'] = symbols['K'] = symbols['L'] = symbols['5'] = 5;
    symbols['M'] = symbols['N'] = symbols['O'] = symbols['6'] = 6;
    symbols['P'] = symbols['R'] = symbols['S'] = symbols['7'] = 7;
    symbols['T'] = symbols['U'] = symbols['V'] = symbols['8'] = 8;
    symbols['W'] = symbols['X'] = symbols['Y'] = symbols['9'] = 9;
}

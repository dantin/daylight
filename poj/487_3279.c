#include <stdio.h>

#define SIZE 7
#define LINE  50
#define SYMBOL 255

void init_symbol_table(char *symboles);

int main(int argc, char *argv[])
{
    int i, n;
    char line[LINE];
    char symbolTable[SYMBOL];

    init_symbol_table(symbolTable);

    scanf("%d", &n);
    for(i = 0; i < n; ++i)
    {
        scanf("%s", &line);

        printf("%s\n", line);
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

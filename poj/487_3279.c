#include <stdio.h>

#define SIZE 100000
#define LINE  51
#define SYMBOL 255
#define TIMES 6

void init_symbol_table(char *symboles);
void heap_sort(int source[], int size);
void max_heap(int source[], int size);
void max_heapify(int source[], int i, int size);
void print_phone(int phone, int freq);

int main(int argc, char *argv[])
{
    int i, j, n, times;
    char line[LINE];
    char symbolTable[SYMBOL];
    int phones[SIZE];

    int freq = 1;
    int dirty = 0;

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
    heap_sort(phones, n);

    for(i = 0; i < n - 1; ++i)
    {
        if(phones[i] == phones[i+1])
        {
            ++freq;
        }
        else
        {
            if(freq >= 2)
            {
                print_phone(phones[i], freq);
                freq = 1;
                dirty = 1;
            }
        }
    }
    if(freq >= 2)
    {
        print_phone(phones[i], freq);
        freq = 1;
        dirty = 1;
    }
    if(dirty == 0)
    {
        printf("No duplicates.");
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

/**
 * Heap sort
 *
 *   source: unsorted elements array.
 *     size: length of array.
 */
void heap_sort(int source[], int size)
{
    int t;
    int i;

    max_heap(source, size);
    for(i = size - 1; i >= 1; --i)
    {
        t = source[i];
        source[i] = source[0];
        source[0] = t;
        --size;
        max_heapify(source, 0, size);
    }
}

void max_heap(int source[], int size)
{
    int i;

    for(i = (size - 1)/2; i >=0; --i)
    {
        max_heapify(source, i, size);
    }
}

void max_heapify(int source[], int i, int size)
{
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int larget;

    if(left < size && source[left] > source[i])
    {
        larget = left;
    }
    else
    {
        larget = i;
    }
    if(right < size && source[right] > source[larget])
    {
        larget = right;
    }

    if(larget != i)
    {
        int temp;
        temp = source[i];
        source[i] = source[larget];
        source[larget] = temp;

        max_heapify(source, larget, size);
    }
}

void print_phone(int phone, int freq)
{
    printf("%03ld-%04ld %d\n", phone/ 10000, phone%10000, freq);
}

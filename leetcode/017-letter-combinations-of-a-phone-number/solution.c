#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETTER_SIZE 10

void print_array(char **array, int size)
{
    int i;

    printf("[");
    for (i = 0; i < size; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("\"%s\"", array[i]);
    }
    printf("]\n");
}

char **letter_combinations(char *digits, int *return_size)
{
    char *letter_matrix[LETTER_SIZE] = {"", " ", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int letter_length[LETTER_SIZE] = {0};
    int i, j, k;

    // initialize `letter_length` which keep the lenth of letters identified by number.
    for (i = 0; i < LETTER_SIZE; i++) {
        letter_length[i] = strlen(letter_matrix[i]);
    }
    
    int empty = 1;                   // flag describes whether the result is empty?
    int count = 1;                   // size of result array.
    int digits_len = strlen(digits); // length of the input digits.
    
    // check total size of the result array.
    for (i = 0; i < digits_len; i++) {
        int idx = digits[i] - '0';
        if (letter_length[idx] > 0) {
            empty = 0;
            count *= letter_length[idx];
        }
    }

    // return directly if the input `digits` is empty.
    if (empty) {
        *return_size = 0;
        return NULL;
    }

    // initialize result array.
    *return_size = count;
    char **letters = malloc(sizeof(char *) * count);
    for (i = 0; i < count; i++) {
        letters[i] = malloc(digits_len + 1);
        memset(letters[i], 0, digits_len + 1);
    }

    int freq = 1;  // frequency of one character
    for (i = digits_len - 1; i > 0; i--) {
        int n = digits[i] - '0';
        if (letter_length[n] > 0) {
            freq *= letter_length[n];
        }
    }

    // padding result array.
    int col = 0;
    for (i = 0; i < digits_len; i++) {
        int n = digits[i] - '0'; // current character
        if (letter_length[n] > 0) {
            if (i > 0) {
                if (letter_length[n] > 0) {
                    freq /= letter_length[n];
                }
            }
            for (j = 0; j < count; j++) {
                k = (j / freq) % letter_length[n];
                letters[j][col] = letter_matrix[n][k];
            }
            col++;
        }
    }

    return letters;
}

int main(int argc, char **argv)
{
    int size = 0;
    char *digits = "23";

    char **letters = letter_combinations(digits, &size);

    printf(" Input: %s\n Output: ", digits);
    print_array(letters, size);
    free(letters);

    return 0;
}

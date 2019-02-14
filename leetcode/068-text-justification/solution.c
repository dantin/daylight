#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
    char **words;
    int len;
    int max_width;
};

void print_strs(char **words, int size)
{
    int i;

    if (size < 1) {
        printf("[]\n");
        return;
    }

    printf("[\"%s\"", words[0]);
    for (i = 1; i < size; i++) {
        printf(", \"%s\"", words[i]);
    }
    printf("]\n");
}

/**
 * Fill a line using <SPACE>.
 *
 *  line:          line placeholder.
 *  len:           original length of line without space padding.
 *  words:         words array.
 *  word_lens:     words length array.
 *  max_size:      target length after padding.
 *  even_spaces:   average space for each word.
 *  remain_spaces: remaining space not used.
 *  start:         start index.
 *  end:           end index.
 */
void line_fill(char *line, int len, char **words, int *word_lens, int max_size,
               int even_spaces, int remain_spaces, int start, int end)
{
    int i, j;
    char *p = line;
    for (i = start; i < end; i++) {
        memcpy(p, words[i], word_lens[i]);
        p += word_lens[i];
        if (i < end - 1) {
            // padding space.
            for (j = 0; j < even_spaces; j++) {
                *p++ = ' ';
            }
            // padding eagerly.
            if (remain_spaces > 0) {
                *p++ = ' ';
                remain_spaces--;
            }
        }
    }
    while (p - line < max_size) {
        *p++ = ' ';
    }
    *p++ = '\0';
}

char **full_justify(char **words, int words_size, int max_width, int *return_size)
{
    int i, cap = 100;
    int count = 0;  // count is the length of return size.

    char **lines = malloc(cap * sizeof(char *));
    for (i = 0; i < cap; i++) {
        lines[i] = malloc(max_width + 1);
    }

    int *word_lens = malloc(words_size * sizeof(int));
    for (i = 0; i < words_size; i++) {
        word_lens[i] = strlen(words[i]);
    }

    int wc = 0;     // wc is the word count.
    int len = 0;    // len is total length of words with character and space.
    int start = 0;  // start is the first word position of current line.
    int chars = 0;  // chars is total length of words with character only.
    for (i = 0; i < words_size; i++) {
        if (len + word_lens[i] > max_width) {
            // keep current word to the next loop.
            count++;
            int even_spaces = wc == 1 ? 0 : (max_width - chars) / (wc - 1);
            int remain_spaces = wc == 1 ? 0 : (max_width - chars) % (wc - 1);
            line_fill(lines[count], len, words, word_lens, max_width, even_spaces, remain_spaces, start, i);
            wc = 1;
            len = word_lens[i] + 1;
            chars = word_lens[i];
            start = i;
        } else if (len + word_lens[i] == max_width) {
            // consume it.
            count++;
            chars += word_lens[i];
            int even_spaces = wc == 0 ? 0 : (max_width - chars) / wc;
            int remain_spaces = wc == 0 ? 0 : (max_width - chars) % wc;
            line_fill(lines[count], len, words, word_lens, max_width, even_spaces, remain_spaces, start, i + 1);
            wc = 0;
            len = 0;
            chars = 0;
            start = i + 1;
        } else {
            chars += word_lens[i];
            /* at least one space */
            len += word_lens[i] + 1;
            wc++;
        }
    }

    if (wc > 0) {
        char *p = lines[count];
        for (i = start; i < start + wc; i++) {
            memcpy(p, words[i], word_lens[i]);
            p += word_lens[i];
            if (i < start + wc - 1) {
                *p++ = ' ';
            }
        }
        while (p - lines[count] < max_width) {
            *p++ = ' ';
        }
        *p++ = '\0';
        count++;
    }

    *return_size = count;
    return lines;
}

int main(int argc, char **argv)
{
    char *words1[] = {"This", "is", "an", "example", "of", "text", "justification."};
    int len1 = sizeof(words1) / sizeof(char *);
    int width1 = 16;
    char *words2[] = {"What", "must", "be", "acknowledgment", "shall", "be"};
    int len2 = sizeof(words2) / sizeof(char *);
    int width2 = 16;
    char *words3[] = {"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain", "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do"};
    int len3 = sizeof(words3) / sizeof(char *);
    int width3 = 20;

    struct Object inputs[] = {
        {.words = words1, .len = len1, .max_width= width1},
        {.words = words2, .len = len2, .max_width= width2},
        {.words = words3, .len = len3, .max_width= width3},
    };
    int i, j, return_size, len = sizeof(inputs) / sizeof(struct Object);
    int indent = 2;

    for (i = 0; i < len; i++) {
        char **words = inputs[i].words;
        int size = inputs[i].len;
        int max_width = inputs[i].max_width;

        printf("\n Input:\n words = ");
        print_strs(words, size);
        printf(" maxWidth = %d\n", max_width);

        char **justified = full_justify(words, size, max_width, &return_size);
        printf(" Output:\n");
        if (return_size < 1) {
            printf("[]\n");
            continue;
        }
        printf("[\n%*s", indent, "");
        printf("\"%s\"", justified[0]);
        for (j = 1; j < return_size; j++) {
            printf(",\n%*s\"%s\"", indent, "", justified[j]);
        }
        printf("\n]\n");
    }

    return EXIT_SUCCESS;
}

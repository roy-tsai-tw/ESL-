#include<stdio.h>
#include<string.h>
#include<ctype.h>

void wr_upper(FILE* filew, char inpc) {
    // Only when seeing lower case letters that we change to upper.
    // All other char's all write to filew as is
    if (inpc >= 'a' && inpc <= 'z')
        fputc(inpc-32, filew);
    else
        fputc(inpc, filew);
}

void counting(FILE* filer, FILE* filew,
              int* ln_ct, int* ch_ct, int* up_ct, int* wd_ct) {
     char inpc = fgetc(filer), prev_ln = 0, prev_wd = 0;

     while (inpc != EOF) {
         wr_upper(filew, inpc);
         // Counting lines
         // At seeing a \n then add 1 to line count.
         // Notice that:
         // 1. the word before \n needs to be counted
         // 2. for consecutive \n, still each \n is a line
         if (inpc == '\n') {
            (*ln_ct)++;
            (*wd_ct)++;
         }

         // At each space a new word is found.
         // Notice that:
         //   1. the word before the end of the line, i.e. \n, is
         //      counted above
         //   2. consecutive spaces needs to be ignored
         if (inpc == ' ') {
            if (!prev_wd) {
                (*wd_ct)++;
               prev_wd = 1;
            }
         } else {
            if (prev_wd)
                prev_wd = 0;
         }

         // Use ASCII values between A and Z to count upper case letters
         // and characters
         if (inpc >= 'A' && inpc <= 'Z') {
            (*up_ct)++;
            (*ch_ct)++;
         }

         // Then also count lower case letters and digits as characters.
         // In this assignment we do not count other symbols as characters.
         if ((inpc >= 'a' && inpc <= 'z') ||
             (inpc >= '0' && inpc <= '9'))
            (*ch_ct)++;

         // Get next character
         inpc = fgetc(filer);
     }
     // At EOF a line and a word are met
     (*ln_ct)++;
     (*wd_ct)++;

     return;
}

int main(int argc, char*argv[])
{
    FILE *filer,*filew ;
    int line_ct = 0, char_ct = 0, upper_ct = 0, word_ct = 0;
    char inpc;

    if (argc != 2) {
        printf("Please give the input file name.\n");
        return 0;
    }

    filer = fopen(argv[1],"r") ;
    if(!filer) {
        printf("Open input file failed!\n");
        return 0 ;
    }

    filew = fopen("UPPER","w");
    counting(filer, filew, &line_ct, &char_ct, &upper_ct, &word_ct);

    printf("In %s:\n", argv[1]);
    printf("\tNumber of lines: %d\n", line_ct);
    printf("\tNumber of characters: %d\n", char_ct);
    printf("\tNumber of upper case letters %d\n", upper_ct);
    printf("\tNumber of words: %d\n", word_ct);

    return 0 ;
}

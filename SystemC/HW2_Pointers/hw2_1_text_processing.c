//===========================================================================//
// SystemC Assignment2 - Pointers                                            //
// file: hw2_1_text_processing.c                                             //
// description: Count the number of lines, characters, uppercase alphabets,  //
//              and words, and then save the file in uppercase.              //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 10/12/2021                                                          //
//===========================================================================//

#include <stdio.h>


void CountFile(FILE *ifp);
void ToUpper(FILE *ifp);

int main(int argc, char *argv[]){
    
    FILE *fp;
    char * prog = argv[0];  /* program name for errors */

    if (argc == 1) {
        printf("You didn't type the name of the text file.\
               Please type it.");
    }
    else {
        if ((fp = fopen(argv[1], "r")) == NULL) {
            
            fprintf(stderr, "%c: can't open %c\n", prog, *argv);
        }
        else {
            CountFile(fp);
            rewind(fp);     /* bring the pointer back to the front */
            ToUpper(fp);
            fclose(fp);
        }
    }
    
    return(0);
}

void CountFile(FILE *ifp) {

    int c = 0;
    int space = 0;
    int space_line = 0;
    int line_number = 0;
    int char_number = 0;
    int upper_number = 0;
    int word_number = 0;

    while ((c = getc(ifp)) != EOF) {

        if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) ||
            ((c >= '0') && (c <= '9'))) {
            char_number++;

            if ((c >= 'A') && (c <= 'Z')) {
                upper_number++;
            }
            /* reset continuous space and line flags to 0 */
            space = 0;
            space_line = 0;
        }
        else if ((c == ' ') || (c == '\n')) {
            /* continuous space or \n only counts for 1 word */
            if((space == 0) && (space_line == 0)){
                word_number++;
            }
            if(c == ' '){
                space++;
            }
            if(c == '\n'){
                space_line++;
                line_number++;
            }
            
        }
    }
    
    /* add 1 for EOF */
    line_number++;
    word_number++;
    
    printf("Line Number = %d\n", line_number);
    printf("Character Number = %d\n", char_number);
    printf("Uppercase Number = %d\n", upper_number);
    printf("Word Number = %d\n", word_number);
}

void ToUpper(FILE *ifp) {

    int c = 0;
    FILE *fp_upper = fopen("UPPER.txt", "w");

    while ((c = getc(ifp)) != EOF) {
        
        if ((c >= 'a') && (c <= 'z')) {
            c = c - 32;
        }
        fputc(c, fp_upper);
    }
    
    fclose(fp_upper);
}
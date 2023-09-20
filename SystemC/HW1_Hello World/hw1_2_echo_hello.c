//============================================================================//
// SystemC Assignment1 - Hello World                                          //
// file: hw1_2_echo_hello.c                                                   //
// description: main file print out the sentence you type and another line    //
//              with "Hello World!"                                           //
// authors: Tsung-Ying(Roy) Tsai                                              //
// date: 10/4/2021                                                            //
//============================================================================//

#include <stdio.h>

int main(int argc, char *argv[]){
    printf("Hello World!\n");
    for(int i = 1; i < argc; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
    return(0);
}

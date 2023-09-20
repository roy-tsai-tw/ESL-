//============================================================================//
// SystemC Assignment1 - Hello World                                          //
// file: hw1_1_run_hello.c                                                    //
// description: main file print out "ExecutableName says Hello World!"        //
// authors: Tsung-Ying(Roy) Tsai                                              //
// date: 10/4/2021                                                            //
//============================================================================//

#include <stdio.h>

int main(int argc, char *argv[]){

    printf("%s says ", argv[0]);
    printf("Hello World!\n");
    return(0);
}

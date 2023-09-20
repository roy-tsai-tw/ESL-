//===========================================================================//
// SystemC Assignment2 - Pointers                                            //
// file: hw2_2_pointers.c                                                    //
// description: allocate argv[1] bytes of memory, assign value, and print.   //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 10/12/2021                                                          //
//===========================================================================//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    /* dynamically assign memory spaces */
    char *memory_array;
    int memory_size = atoi(argv[1]);
    printf("Memory Size = %d\n", memory_size);
    memory_array = (char*)malloc(sizeof(char) * memory_size);
    
    /* protection if the pointer points to NULL */
    if (memory_array == NULL) {
        printf("Invalid Pointer!\n");
    }
    else {
        /* continuously assign A~Z, 1~9 into the memory spaces */
        for (int i = 0; i < memory_size; i++) {
            if (i % 35 < 26) {
                *(memory_array + i) = 'A' + i % 35;
            }
            else {
                *(memory_array + i) = '1' + i % 35 - 26;
            }
        }
    }
    
    /* new int* pointer to print the memory content */
    int *memory_arr_int = (int*)memory_array;
    int i = 0;
    int iteration_number = memory_size / 4;
    do {
        if(iteration_number != 0){
            printf("memory_arr_int[%d] = %d.\n", i, *(memory_arr_int + i));
            /* subtract 1 from the value after it is printed */
            *(memory_arr_int + i) = *(memory_arr_int + i) - 1;
            printf("memory_arr_int[%d] = %d. after subtract 1\n", i, 
            *(memory_arr_int + i));
            i++;            
        }
        else{
            break;
        }
        
    } while (i < iteration_number);
    
    /* free the memory spaces */
    free(memory_array);
    
    return(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("ERROR!! Please give the size of the memory");
	return 0;
    }
	
    int size = atoi(argv[1]);

    char *str = (char*)malloc(size);
    char *ptr = str;
    char data = 'A';

    for (int i = 0; i < size; i++) {
        *ptr = data;
        ptr++;
        if (data == 'Z') {
            data = '1'; 
        } else if (data == '9') {
            data = 'A';              
        } else {
            data++;
        }
    }

    printf("%s\n",str);
    int *pointer = (int*)str;

    int j = size/4;
    int i = 0;

    // use while loop to prevent argv[1] is less than 4
    while (j > 0) {
        printf("%d - ", pointer[i]); // print int before the subtraction
        pointer[i]--;
        printf("%d\n", pointer[i]); // print int after the subtraction
        j--;
        i++;
    }

    free(str);
    return 0;
}
	

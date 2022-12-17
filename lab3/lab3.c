//In the initial sequence of real numbers, find those whose fractional part, represented as an integer, exceeds their integer part in absolute value. Form from given numbers
//new sequence by removing them from the original.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab3.h"

int main() {
    double *arr = NULL, elem = 0;
    int len = 0, size = 0, N, n = 0;
    int pos = 0;
    arr = enterArr(&len);
    printArr(arr, len);
    size = len;
    printf("PLEASE ENTER N:");
    N = checkValuesInt(N);
    while(1){
        printf("PLEASE CHOOSE COMMAND:\n1 - ADD ELEM\n2 - DEL ELEM\n3 - TASK (IN THE INITIAL SEQUENCE OF REAL NUMBERS,\nFIND THOSE WHOSE FRACTIONAL PART,\nREPRESENTED AS AN INTEGER, EXCEEDS\nTHEIR INTEGER PART IN ABSOLUTE >        n = checkValuesInt(n);
        switch (n) {
            case 1:
                printf("PLEASE ENTER X:");
                checkValuesDouble(&elem);
                printf("PLEASE ENTER INDEX:");
                pos = checkValuesInt(pos);
                if(size == len){
                    size += N;
                    arr = (double *) realloc(arr, (size) * sizeof(double));
                }else{
                    arr = (double *) realloc(arr, (len + 1) * sizeof(double));
                }
                arr = addElemArr(arr, &len, elem, pos);
                break;
            case 2:
                printf("PLEASE ENTER INDEX:");
                pos = checkValuesInt(pos);
                size = len + N - 1;
                arr = DelElemArr(arr, &len, size, pos);
                break;
            case 3:
                arr = task(arr, &len, &size, N);
                break;
            case 4:
                printArr(arr, len);
                printf("capacity = %d, size = %d\n", len, size);
                break;
            case 5:
                free(arr);
                printf("BYE)");
                return 0;
            default: printf("!PLEASE ENTER CORRECT!  \n");
        }
    }
}

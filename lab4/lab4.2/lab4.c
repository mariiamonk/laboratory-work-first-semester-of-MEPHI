#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lab42.h"

#define PROMPT "Enter: "

int main() {
    char *input = myreadline(PROMPT);
    while (input != NULL){
        if(input[0] == '\0' || checkline(input) == 0){
                free(input);
                printf("Empty line\n");
                input = myreadline(PROMPT);
                continue;
        }
        clock_t  start, end;
        printf("Input:\"%s\"\n", input);
        start = clock(); 
        char *output = task(input);
        end = clock();
        double time = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("Task:\"%s\"\nTime: %.20f\n", output, time);
        free(output);
        free(input);
        input = myreadline(PROMPT); 
    }
    free(input);
    return 0;
}

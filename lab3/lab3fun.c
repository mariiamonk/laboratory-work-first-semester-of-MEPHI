#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab3.h"

double* enterArr(int *len){//схема
    int flag = 0;
    printf("ENTER ARRAY LENGTH:");
    while ((flag <= 1) || (*len > 0)){
        flag = scanf("%d", len);;
        scanf("%*[^\n]");
        if (flag == EOF){break;}
        if (flag == 1){break;}
        if (flag < 1){
            printf("ERROR\nPLEASE ENTER CORRECT VALUES:\n");
        }
    }
    double *arr = (double*) malloc((*len) * sizeof(double));
    printf("ENTER ELEMENTS:\n");
    for(int i = 0; i < *len; ++i){
        while (flag <= 1) {
            flag = scanf("%lf", &arr[i]);
            scanf("%*[^\n]");
            if (flag == EOF) { break; }
            if (flag == 1) { break; }
            if (flag < 1) {
                printf("ERROR\nPLEASE ENTER CORRECT VALUES:\n");
            }
        }
    }
    return arr;
}

void printArr(double *arr, int len){//схема
    for(int i = 0; i < len; ++ i){
        printf("%lf ", arr[i]);
    }
    printf("\n");
}

double* addElemArr(double *arr, int *len, double elem, int pos){//схема
    for (int i = *len - 1; i >= pos; i--) {
        arr[i + 1] = arr[i];
    }
    arr[pos] = elem;
    *len += 1;
    return arr;
}

double* DelElemArr(double *arr, int *len, int size, int pos){//схема
    double* n_arr;
    n_arr = (double*)malloc((size) * sizeof(double));
    for(int i = 0;i < pos; ++i){
        n_arr[i]  = arr[i];
    }
    for (int i = pos; i < *len - 1; ++i){
        n_arr[i] = arr[i+1];
    }
    *len -= 1;
    free(arr);
    return n_arr;
}

double factPart(double x){
    double n_x;
    long double temp = x;
    long int temp2 = 1;
    while (fmod(temp, 10) !=0){
        temp = temp * 10;
        temp2 *= 10;
    }
    temp /= 10;
    temp2 /= 10;
    n_x = fmod(temp, temp2);
    return n_x;
}

double* task(double *arr, int *len, int *size, int N){//схема
    double *new_arr = NULL, n;
    int n_len = 0;
    for(int i = 0; i < *len; ++i){
        modf(arr[i], &n);
        if(factPart(arr[i]) > n){
            new_arr = (double *) realloc(new_arr, (n_len + 1) * sizeof(double));
            new_arr[n_len] = factPart(arr[i]);
            n_len++;
            *size = *len + N - 1;
            arr = DelElemArr(arr, len, *size, i);
            i--;
        }
    }
    printArr(new_arr,n_len);
    free(new_arr);
    return arr;
}

int checkValuesInt(int a){
    int flag = 0;
    flag = scanf("%d", &a);
    while (flag <= 1){
        if (flag == EOF){return 0;}
        if (flag == 1 && a >= 0){return a;}


        else{
            printf("ERROR\nPLEASE ENTER CORRECT VALUES:\n");
            scanf("%*[^\n]");
            flag = scanf("%d", &a);
        }


    }
}

int checkValuesDouble(double *b){
    int flag = 0;
    while (flag <= 1){
        flag = scanf("%lf", b);
        scanf("%*[^\n]");
        if (flag == EOF){return 0;}
        if (flag == 1){break;}
        if (flag < 1){
            printf("ERROR\nPLEASE ENTER CORRECT VALUES:\n");
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab42.h"

#define SPA " \t"

size_t mystrlen(const char *s) {
    int res = 0;
    while (*s) {
        ++s; ++res;
    }
    return res;
}

char* myreadline(const char *prompt){
    printf("%s", prompt);
    char *ptr = NULL;
    char buf[81] = {0};
    int n = 0, len = 0;
    do{
       n = scanf("%80[^\n]", buf);
       if(n < 0){
          free(ptr);
          return NULL;
       }
       else if(n == 0) {
          scanf("%*c");
       }
       else{
          int buf_len = mystrlen(buf);
          int ptr_len = len + buf_len;
          ptr = realloc(ptr, ptr_len + 1);
          memcpy(ptr + len, buf, buf_len);
          len = ptr_len;
       }
    } while(n > 0);
    if(len > 0) ptr[len] = '\0';
    else ptr = calloc(1, sizeof(char));
    return ptr;
}

void* mymemcpy(void* ptr, const void* n_arr, size_t size){
    const char* n_arr = (char*)n_arr;
    char* n_ptr = (char*)ptr;
    for (size_t i = 0; i < size; ++i){
        *n_ptr++ = *n_arr++;
    }
    return ptr;
}

char* mystrcpy(char* str, const char* ptr){
     int len = mystrlen(ptr);
     for(int i = 0; i < len; ++i){
        str[i] = ptr[i];
     }str[len] = '\0';
     return str;
}

char* mystrchr (const char *str, int ch){
    int i = 0;
    while (str[i] && str[i] != ch) ++i;
    return ch == str[i] ? (char*)str + i : NULL;
}

char* mystrtok(char* str, const char* ptr){
     static char * mid = 0;
     if (str) mid = str;
     if ((mid == 0) || (*mid == 0)) return 0;
     char *c = mid;
     while (mystrchr(ptr, *c)) ++c;
     if (c == 0) return 0;
     char *start = c;
     while(c && (mystrchr(ptr,*c) == 0)) ++c;
     if (*c == 0){
          mid = c;
          return start;
     }
     *c = 0;
     mid = c + 1;
     return start;
}

char *task(const char *str){
    char *s = malloc((mystrlen(str) + 1) * sizeof(char));
    s = mystrcpy(s, str);
    char letter;
    int s_len = mystrlen(s);
    char *res = calloc(s_len + 1, sizeof(char));
    char *mid = calloc(s_len + 1, sizeof(char));
    int len = 0, mid_len = 0;
    char *word = mystrtok(s, SPA);
    while (word != NULL) {
        letter = word[0];
        word = mystrtok(NULL, SPA);
    }
    printf("Letter:%c\n", letter);
    free(s);
    s = malloc((mystrlen(str) + 1) * sizeof(char));
    s = mystrcpy(s, str);
    word = mystrtok(s, SPA);
    while (word != NULL) {
        int w_len = mystrlen(word);
        if (word[w_len - 1] == letter) {
            mymemcpy(res + len, word, w_len * sizeof(char));
            len += w_len;
            res[len] = ' ';
            ++len;
        }else{
            mymemcpy(mid + mid_len, word, w_len *  sizeof(char));
            mid_len += w_len;
            mid[mid_len] = ' ';
            ++mid_len;
        }
        word = mystrtok(NULL, SPA);
    }
    free(s);
    free(word);
    mymemcpy(res + len, mid, mid_len * sizeof(char));
    len += mid_len;
    if (len > 0) {
        --len;
    }
    free(mid);
    res[len] = '\0';
    res = realloc(res, (len + 1) * sizeof(char));
    return res;
}

int checkline(char* str){
    int n = 0;
    for(int i = 0; i < mystrlen(str);++i){
          if(str[i] != '\t' && str[i] != ' ')++n;
    }
    if(n == 0)return 0;
    else return 1;
}

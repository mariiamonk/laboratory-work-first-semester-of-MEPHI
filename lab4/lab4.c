#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <time.h>

#define PROMPT "Enter: "
#define SPA " \t"

char *task(const char* str);
int checkline(char* str);

int main() {
    char *input = readline(PROMPT);
    while (input != NULL) {
        if(input[0] == '\0' || checkline(input) == 0){
                free(input);
                printf("Empty line\n");
                input = readline(PROMPT);
                continue;
        }
        clock_t start, end;
        printf("Input:\"%s\"\n", input);
        start = clock();
        char *output = task(input);
        end = clock();
        double time = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("Task:\"%s\"\nTime:%.20f\n", output, time);
        free(input);
        free(output);
        input = readline(PROMPT);
    }
    free(input);
    return 0;
}

char *task(const char *str){
    char *s = strdup(str);
    char letter;
    int s_len = strlen(s);
    char *res = calloc(s_len + 1, sizeof(char));
    char *mid = calloc(s_len + 1, sizeof(char));
    int len = 0, mid_len = 0;
    char *word = strtok(s, SPA);
    while (word != NULL) {
        letter =  word[0];
        word = strtok(NULL, SPA);
    }
    printf("letter:%c\n", letter);
    free(s);
    s = strdup(str);
    word = strtok(s, SPA);
    while (word != NULL) {
        int w_len = strlen(word);
        if (word[w_len - 1] == letter) {
            memcpy(res + len, word, w_len * sizeof(char));
            len += w_len;
            res[len] = ' ';
            ++len;
        }else{
            memcpy(mid + mid_len, word, w_len *  sizeof(char));
            mid_len += w_len;
            mid[mid_len] = ' ';
            ++mid_len;
        }
        word = strtok(NULL, SPA);
    }
    free(s);
    free(word);
    memcpy(res + len, mid, mid_len * sizeof(char));
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
    for(int i = 0; i < strlen(str);++i){
          if(str[i] != '\t' && str[i] != ' ') ++n;
    }
    if(n == 0)return 0;
    else return 1;
}

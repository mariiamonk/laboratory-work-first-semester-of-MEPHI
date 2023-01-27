/*Структура данных
Абонент:
• ФИО (строка произвольной длины);
• номер телефона (строка длиной до 16 символов, которая может включать в себя цифры, пробелы и знак «+» в начале);
• время последнего звонка (целочисленное значение, соответствующее временной метке в формате UNIX time).
Алгоритмы сортировки
1. Чётно-нечётная сортировка (Odd-even sort).
2. Сортировка вставками (Insertion sort).*/

#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

const static int ARRAY_INIT_SIZE = 10;

struct abonent {
    char *fullname;
    char phone_number[17];
    time_t last_call;
};

int set_full_name(struct abonent *abonent, char *fullname) {
    for (int i = 0; i < strlen(fullname); i++)
        if (!(isalpha(fullname[i]) || fullname[i] == ' '))
            return 1;
    if ((abonent->fullname = strdup(fullname)) == NULL)
        return 2;
    return 0;
}

int set_phone_number(struct abonent *abonent, const char phone_number[17]) {
    if (phone_number[0] != '+')
        return 1;
    for (const char *c = &(phone_number[1]); c < phone_number + 16 && *c != '\0'; c++)
        if (!(isdigit(*c) || *c == ' '))
            return 1;
    strcpy_s(abonent->phone_number, 16, phone_number);
    return 0;
}

int set_last_call(struct abonent *abonent, char *last_call_str) {
    int year, month, day, hour, min, sec;

    time_t result;
    if (sscanf(last_call_str, "%2d.%2d.%4d %2d:%2d:%2d", &day, &month, &year, &hour, &min, &sec) == 6) {
        struct tm breakdown = {0};
        breakdown.tm_year = year - 1900; /* years since 1900 */
        breakdown.tm_mon = month - 1;
        breakdown.tm_mday = day;
        breakdown.tm_hour = hour;
        breakdown.tm_min = min;
        breakdown.tm_sec = sec;

        if ((result = mktime(&breakdown)) == (time_t) -1)
            return 2;

        abonent->last_call = result;
        return 0;
    } else {
        return 1;
    }
}

void my_len(const char *st, int *len) {
    char c = st[0];
    int i = 0;
    while (c != 0) {
        i++;
        c = st[i];
    }
    *len = i;
}

void mcp(char *dest, char *src, int n) {

    int *temp = (int *) malloc(n * sizeof(int));
    if (!temp)
        return;

    for (int i = 0; i < n; i++)
        temp[i] = src[i];

    for (int i = 0; i < n; i++)
        dest[i] = temp[i];

    free(temp);
}

char *in_str(FILE *file) {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n;
    do {
        n = fscanf(file, "%80[^\n]", buf);
        if (n == EOF) {
            return NULL;
        } else if (n > 0) {
            int milen;
            my_len(buf, &milen);
            int chunk_len = milen;
            int str_len = len + chunk_len;
            res = (char *) realloc(res, sizeof(char) * (str_len + 1));
            mcp(res + len, buf, chunk_len);
            len = str_len;
        } else {
            fscanf(file, "%*c");
        }
    } while (n > 0);
    if (len > 0) {
        res[len] = '\0';
    } else {
        res = (char *) calloc(1, sizeof(char));
    }

    return res;
}

int read_file(struct abonent *(abonents[]), const char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    *abonents = calloc(ARRAY_INIT_SIZE, sizeof(struct abonent));
    if (file == NULL) {
        free(*abonents);
        *abonents = NULL;
        return -1;
    }

    int i = 0, m = 1, f1, f2, f3;
    char *line;
    char *fullname = NULL;
    char phone_number[17];
    char *last_call_str = NULL;
    while ((line = in_str(file)) != NULL) {
        if (i % ARRAY_INIT_SIZE == 0 && i > 0) {
            struct abonent *new_ptr;
            m++;
            if ((new_ptr = realloc(*abonents, ARRAY_INIT_SIZE * m * sizeof(struct abonent))) == NULL) {
                free(line);
                return i;
            }
            *abonents = new_ptr;
        }
        if (strlen(line) == 0)
            continue;

        char *pos1, *pos2;

        pos1 = strchr(line, ';');
        pos2 = strchr(pos1 + 1, ';');

        if (pos1 == NULL || pos2 == NULL || strchr(pos2 + 1, ';') != NULL || pos2 - pos1 > 16) {
            free(*abonents);
            free(line);
            *abonents = NULL;
            return -2;
        }

        *pos1 = '\0';
        *pos2 = '\0';

        fullname = line;
        f1 = set_full_name(&(*abonents)[i], fullname);
        if (f1 == 1)
            fprintf(stderr, "Invalid fullname %s for %d abonent.\n", fullname, i + 1);
        if (f1 == 2)
            fprintf(stderr, "Error in malloc for fullname %s for %d abonent.\n", fullname, i + 1);
        if (f1)
            (*abonents)[i].fullname = calloc(1, sizeof(char));

        strcpy(phone_number, pos1 + 1);
        (*abonents)[i].phone_number[0] = '\0';
        f2 = set_phone_number(&(*abonents)[i], phone_number);
        if (f2 == 1)
            fprintf(stderr, "Invalid phone number %s for %d abonent.\n", phone_number, i + 1);

        last_call_str = pos2 + 1;
        (*abonents)[i].last_call = 0;
        f3 = set_last_call(&(*abonents)[i], last_call_str);
        if (f3 == 1)
            fprintf(stderr, "Invalid last call %s for %d abonent.\n", last_call_str, i + 1);
        if (!f1 || !f2 || !f3)
            i++;
        free(line);
    }
    fclose(file);
    *abonents = realloc(*abonents, i * sizeof(struct abonent));
    return i;
}

int write_file(struct abonent abonents[], int n, const char *filename) {
    FILE *file;
    file = fopen(filename, "w");
    char last_call_str[21];

    if (file == NULL)
        return 1;
    for (int i = 0; i < n; i++) {
        strftime(last_call_str, 20, "%d.%m.%Y %H:%M:%S", localtime(&abonents[i].last_call));
        fprintf(file, "%s;%s;%s\n", abonents[i].fullname, abonents[i].phone_number, last_call_str);
    }
    fclose(file);
    return 0;
}

enum algorithm {
    quick, odd_even, insertion
};

enum field {
    fullname, phone_number, last_call
};

enum direction {
    direct, reverse
};

static enum direction direction = 0;

int fullname_cmp(const struct abonent *a1, const struct abonent *a2) {
    int out = strcmp(a1->fullname, a2->fullname);
    if (direction == reverse)
        out *= -1;
    return out;
}

int phone_number_cmp(const struct abonent *a1, const struct abonent *a2) {
    int out = strcmp(a1->phone_number, a2->phone_number);
    if (direction == reverse)
        out *= -1;
    return out;
}

int last_call_cmp(const struct abonent *a1, const struct abonent *a2) {
    int out;
    if (a1->last_call > a2->last_call)
        out = 1;
    else if (a1->last_call == a2->last_call)
        out = 0;
    else
        out = -1;
    if (direction == reverse)
        out *= -1;
    return out;
}

void odd_even_sort(struct abonent abonents[], int n, int (*comp)(const struct abonent *, const struct abonent *)) {
    int is_sorted = 0;

    while (!is_sorted) {
        is_sorted = 1;

        for (int i = 1; i <= n - 2; i = i + 2) {
            if (comp(&(abonents[i]), &(abonents[i + 1])) > 0) {
                struct abonent tmp;
                tmp = abonents[i];
                abonents[i] = abonents[i + 1];
                abonents[i + 1] = tmp;
                is_sorted = 0;
            }
        }

        for (int i = 0; i <= n - 2; i = i + 2) {
            if (comp(&(abonents[i]), &(abonents[i + 1])) > 0) {
                struct abonent tmp;
                tmp = abonents[i];
                abonents[i] = abonents[i + 1];
                abonents[i + 1] = tmp;
                is_sorted = 0;
            }
        }
    }
}

void insertion_sort(struct abonent abonents[], int n, int (*comp)(const struct abonent *, const struct abonent *)) {
    int i, j;
    struct abonent key;
    for (i = 1; i < n; i++) {
        key = abonents[i];
        j = i - 1;

        while (j >= 0 && (comp(&(abonents[j]), &key) > 0)) {
            abonents[j + 1] = abonents[j];
            j = j - 1;
        }
        abonents[j + 1] = key;
    }
}

int main(int argc, char *argv[]) {
    int c;
    enum algorithm algorithm = 0;
    enum field field = 0;

    while ((c = getopt(argc, argv, "a:f:d:")) != -1) {

        switch (c) {
            case 'a':
                if (strcmp(optarg, "quick") == 0)
                    algorithm = quick;
                else if (strcmp(optarg, "odd_even") == 0)
                    algorithm = odd_even;
                else if (strcmp(optarg, "insertion") == 0)
                    algorithm = insertion;
                else {
                    fprintf(stderr, "Unknown argument %s for option -%c.\n", optarg, c);
                    return 1;
                }
                break;
            case 'f':
                if (strcmp(optarg, "fullname") == 0)
                    field = fullname;
                else if (strcmp(optarg, "phone_number") == 0)
                    field = phone_number;
                else if (strcmp(optarg, "last_call") == 0)
                    field = last_call;
                else {
                    fprintf(stderr, "Unknown argument %s for option -%c.\n", optarg, c);
                    return 1;
                }
                break;
            case 'd':
                if (strcmp(optarg, "direct") == 0)
                    direction = direct;
                else if (strcmp(optarg, "reverse") == 0)
                    direction = reverse;
                else {
                    fprintf(stderr, "Unknown argument %s for option -%c.\n", optarg, c);
                    return 1;
                }
                break;
            case '?':
                if (optopt == 'a' || optopt == 'b' || optopt == 'c')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option -%c.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character /x%x.\n", optopt);
                return 1;
            default:
                return 1;
        }
    }

    if (argc - optind != 2) {
        fprintf(stderr, "Usage: %s <options> <input filename> <output filename> .\n", argv[0]);
        return 1;
    }

    char *i_fname = argv[optind];
    char *o_fname = argv[optind + 1];

    struct abonent *abonents;

    int n = read_file(&abonents, i_fname);
    if (n == -1) {
        fprintf(stderr, "Error in input file opening %s.\n", i_fname);
        return 1;
    } else if (n == -2) {
        fprintf(stderr, "Invalid input file structure %s.\n", i_fname);
        return 1;
    } else if (n == 0) {
        printf("0 valid abonents");
        return 0;
    }

    if (algorithm == quick) {
        if (field == fullname)
            qsort(abonents, n, sizeof(struct abonent), fullname_cmp);
        else if (field == phone_number)
            qsort(abonents, n, sizeof(struct abonent), phone_number_cmp);
        else
            qsort(abonents, n, sizeof(struct abonent), last_call_cmp);
    } else if (algorithm == odd_even) {
        if (field == fullname)
            odd_even_sort(abonents, n, fullname_cmp);
        else if (field == phone_number)
            odd_even_sort(abonents, n, phone_number_cmp);
        else
            odd_even_sort(abonents, n, last_call_cmp);
    } else {
        if (field == fullname)
            insertion_sort(abonents, n, fullname_cmp);
        else if (field == phone_number)
            insertion_sort(abonents, n, phone_number_cmp);
        else
            insertion_sort(abonents, n, last_call_cmp);
    }

    if (write_file(abonents, n, o_fname))
        fprintf(stderr, "Error in output file opening %s.\n", o_fname);
    free(abonents);
}

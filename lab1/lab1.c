//Given an integer. Determine the number of zeros in the number entry. Receive new number without zero
#include <stdio.h>

void del_zero(int* a){
        int i = 0, b = 0, st = 1;
        while(a* != 0){
                if(*a % 10 != 0){
                        b += (*a % 10) * st;
                        i ++;
                        st *= 10;
                }
                *a /= 10;
        }
        *a = b;
}

int count_zero(int a){
        int count = 0;
        while(a != 0){
                if(a % 10 == 0){
                        count ++;
                }
                a /= 10;
        }
        return count;
}

int main(){
        int a = 0;

        printf("Enter int:   ");
        if(scanf("%d", &a) == 0){
                printf("Error");
                return 0;
        }
        int d_a = a;

        del_zero(&a);

        printf("Answer:   ");
        printf("%d, %d", a, count_zero(d_a));

        return 0;
}

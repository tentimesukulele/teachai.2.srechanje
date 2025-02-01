#include <stdio.h>

int main() {
    int M, N;
    scanf("%d %d", &M, &N); 

    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= i; ++j) {
            printf("*");
        }
        printf("\n");
    }

    for (int i = 0; i < N; ++i) {
        printf("*\n");
    }

    return 0;
}

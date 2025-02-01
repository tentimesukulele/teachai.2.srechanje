#include <stdio.h>

int main() {
    int V, M;

    scanf("%d %d", &V, &M);

    int prodani_kosi = (V / M) * (V / M);

    int preostali_kosi = (V % M) * V;


    printf("%d %d\n", prodani_kosi, preostali_kosi);

    return 0;
}

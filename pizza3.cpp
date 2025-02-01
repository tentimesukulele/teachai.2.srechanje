#include <stdio.h>

int main() {
    int V, M;

    // Preberite dolžino stranice pice (V) in dolžino stranice kvadratka (M)
    scanf("%d %d", &V, &M);

    // Izračunajte število prodanih kosov
    int prodani_kosi = (V / M) * (V / M);

    // Izračunajte preostale kose
    int preostali_kosi = (V % M) * (V / M) + (V / M) * (V % M);

    // Izpišite rezultate
    printf("%d %d\n", prodani_kosi, preostali_kosi);

    return 0;
}

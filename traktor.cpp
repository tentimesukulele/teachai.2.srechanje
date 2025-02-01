#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n); 

    int traktorji[n]; 
    int ugibanja[n];  

    int skupnoTraktorjev = 0;

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &traktorji[i], &ugibanja[i]);
        skupnoTraktorjev += traktorji[i];
    }

    int pravilnaUgibanja = 0;

    for (int i = 0; i < n; ++i) {
        int naslednji = (i + 1) % n; 
        if (ugibanja[i] == traktorji[naslednji]) {
            pravilnaUgibanja++;
        }
    }

    printf("%d\n", skupnoTraktorjev);
    printf("%d\n", pravilnaUgibanja);

    return 0;
}

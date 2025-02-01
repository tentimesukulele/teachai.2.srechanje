#include <stdio.h>

int main() {
    long long N;
    scanf("%lld", &N); 

    int count = 0; 
    int sum = 0; 

    long long temp = N;

    while (temp > 0) {
        sum += temp % 10; 
        temp /= 10; 
        count++; 
    }

    if (N == 0) {
        count = 1; 
        sum = 0;
    }

    printf("%d %d\n", count, sum);
    return 0;
}

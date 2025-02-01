#include <stdio.h>

int main() {
    int M, N;
    
    scanf("%d %d", &M, &N);
    
    int height = 0;
    
    while (height <= M) {
        height += N;
    }
    
    printf("%d\n", height);
    
    return 0;
}

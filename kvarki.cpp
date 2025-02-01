#include <stdio.h>

int main() {
    int up, charm, top, down, strange, bottom;
    scanf("%d %d %d %d %d %d", &up, &charm, &top, &down, &strange, &bottom);
    
    int total_charge = up * 2 + charm * 2 + top * 2 - down - strange - bottom;
    
    if (total_charge == 0) {
        printf("0\n");
        return 0;
    }
    
    int needed = 0;
    

    while (total_charge != 0) {
        if (total_charge > 0) {
            total_charge -= 1;  
        } else {
            total_charge += 2;  
        }
        needed++;
    }
    
    printf("%d\n", needed);
    
    return 0;
}

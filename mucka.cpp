#include <stdio.h>

int main() {
	
	int n;
	scanf ("%d", &n);
	int visina, prejsnja_visina;
	int najvecji_padec = 0;
	
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &visina);
		if ( i != 0 ) {
			if (prejsnja_visina > visina ) {
			int padec = prejsnja_visina - visina;
			if ( padec > najvecji_padec ) {
							najvecji_padec = padec;
					}
			}
		}
		prejsnja_visina = visina;
	}
	printf("%d\n", najvecji_padec);
	return 0;
	
}

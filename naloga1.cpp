#include <stdio.h>

int main() {
	int a = 0;
	scanf("%d", &a);
	int vse = 0;
	for(int n = 0; n < a+1; n++) {
		vse += n;
	}
	printf("Vsota prvih n stevil je: %d\n", vse);
	return 0;
}

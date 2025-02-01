#include <stdio.h>

int main() {
	int cas;
	printf("Vnesi cas: ");
	scanf("%d",  &cas);
	if (cas < 12) {
		printf("Tvoj cas je pred 12 uro dopoldne.\n");
	}else{
		printf("Tvoj cas je za 12 uro dopoldne\n");
	}
	return 0;
}


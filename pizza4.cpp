#include <stdio.h>
int main() {
	int st, st2;
	
	scanf("%d %d", &st, &st2 );
	
	if (st%st2==0){
	printf("%d 0\n", (st / st2) * (st/st2));
		
	}else{
		printf("%d %d\n", (st / st2)*(st / st2), 2*(st/st2)+1);
			}
return 0;
}

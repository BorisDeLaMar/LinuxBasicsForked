#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char cmd[50]; int ans = 0; 
	int *symbol = malloc(sizeof(int)); 
	char* s = malloc(sizeof(char));
	sprintf(cmd, "%s %s", argv[1], argv[2]);
	
	FILE* pipe = popen(cmd, "r");
	if(pipe != NULL)
	{
		while((*symbol = fgetc(pipe)) != EOF)
		{
			sprintf(s, "%d", *symbol);
			if(strcmp(s, "48") == 0) // 48 - код нуля в ASCII
			{
				ans += 1;
			}
		}
	}
	free(s); free(symbol);
	pclose(pipe);

	printf("%d\n", ans);
	return 0;
}

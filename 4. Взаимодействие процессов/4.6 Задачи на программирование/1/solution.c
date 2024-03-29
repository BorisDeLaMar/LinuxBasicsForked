#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char cmd[50]; int ans = 0; char *symbol;
	sprintf(cmd, "%s %s", argv[1], argv[2]);
	
	FILE* pipe = popen(cmd, "r");
	if(pipe != NULL)
	{
		while((*symbol = fgetc(pipe)) != EOF)
		{
			if(strcmp(symbol, "0") == 0)
			{
				ans += 1;
			}
		}
	}
	pclose(pipe);

	printf("%d\n", ans);
	return 0;
}

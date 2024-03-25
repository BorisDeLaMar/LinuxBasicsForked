#include <string.h>
#include <sys/types.h>
#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>

int main()
{
	int child_pid;
	
	chdir("/");
	child_pid = fork();
		
	if(child_pid == 0)
	{
		printf("%d", getpid());
		setsid();
		fclose(stdin);
		fclose(stdout);
		fclose(stderr);
		sleep(10);
	}

	return 0;
}

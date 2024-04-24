#include <unistd.h>  
#include <stdio.h>  
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>

bool flag = true;

void signal_handler(int signal)
{
	if(signal == 23)
		flag = false;		
}

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
		
		signal(SIGURG, signal_handler);
		
		while(1)
		{
			if(!flag)
				return 0;
		}
	}

	return 0;
}

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

int sigusr_1 = 0;
int sigusr_2 = 0;
bool flag = true;

void signal_handler(int signal)
{
	if(signal == 10)
		sigusr_1 += 1;
	else if(signal == 12)
		sigusr_2 += 1;
	else if(signal == 15)
		flag = false;
}

int main()
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGTERM, signal_handler);	

	while(flag)
	{
		usleep(500000);
	}
	printf("%d %d\n", sigusr_1, sigusr_2);

	return 0;
}

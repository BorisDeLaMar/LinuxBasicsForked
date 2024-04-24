#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>

struct topchik
{
	int value;
	int read_bytes;	
};

struct topchik read_and_count(int f)
{
	char buf[10] = {0};
	int bytes = read(f, buf, 10);
	int ans = strtol(buf, NULL, 10);
	struct topchik answer = {.value = ans, .read_bytes = bytes};
	return answer;
}

int main()
{

	int f1 = open( "in1", O_RDONLY | O_NONBLOCK );
	int f2 = open( "in2", O_RDONLY | O_NONBLOCK );

	int sum = 0; bool ch1_flag = true; bool ch2_flag = true;

	if (!(f1 && f2) )
	{
		printf ("Error with opening pipes\n");
		return 0;
	}
	
	fd_set read_set;
	
	while(1)
	{
		FD_ZERO(&read_set);
		if(ch1_flag)
			FD_SET(f1, &read_set);
		if(ch2_flag)
			FD_SET(f2, &read_set);
		
		struct timeval timer = (struct timeval) {5, 0};
		int result = select(f2+1, &read_set, NULL, NULL, &timer);
		if(result)
		{
			if(FD_ISSET(f1, &read_set))
			{
				struct topchik ans = read_and_count(f1);
				if(ans.read_bytes > 0)
					sum += ans.value;
				else if(ans.read_bytes == 0)
				{
					ch1_flag = false;
				}
			}
			if(FD_ISSET(f2, &read_set))
			{
				struct topchik ans = read_and_count(f2);
				if(ans.read_bytes > 0)
					sum += ans.value;
				else if(ans.read_bytes == 0)
				{
					ch2_flag = false;
				}
			}
		}
		if((ch1_flag == false) && (ch2_flag == false))
		{
			break;
		}
	}
	
	printf("%d\n", sum);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>

int recursive_search(int pid)
{
	char *path = malloc(1000*sizeof(char)); FILE* file = NULL; int ppid;
	sprintf(path, "/proc/%d/stat", pid);
	file = fopen(path, "r");
	if(file != NULL)
	{
		fscanf(file, "%*d %*s %*c %d", &ppid);
		free(path);
		fclose(file);
	} else{
		printf("Can't open file %s or read ppid field\n", path);
		free(path);
		return 0;
	}
	return ppid;
}

int main(int argc, char *argv[])
{
	int pid = atoi(argv[1]);
	while(true)
	{
		printf("%d\n", pid);
		pid = recursive_search(pid);
		if(pid == 0){
			return 2;
		}
		if(pid == 1)
		{
			break;
		}
	}
	printf("%d\n", pid);
	return 0;
}

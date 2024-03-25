#include <string.h>
#include <sys/types.h>
#include <dirent.h>  
#include <stdio.h>  
#include <stdlib.h>

int filter(struct dirent **namelist, int ppid, int n)
{
	int i; int ans = 0;
	for(i = 0; i < n; i++)
	{
		char *path = malloc(1000*sizeof(char));  
		int ppid_read; int pid;
		sprintf(path, "%s%s%s", "/proc/", namelist[i]->d_name, "/stat");
		FILE* f = NULL;
		if((f = fopen(path, "r")) == NULL)
		{
			free(path);
		} else
		{
			fscanf(f, "%d", &pid);
			fscanf(f, "%*s %*c %d", &ppid_read);
			if(ppid_read == ppid){
				ans += 1;
				ans += filter(namelist, pid, n);
				free(path);
				fclose(f);
			}
		}
	}		
	return ans;
}

int main(int argc, char *argv[])
{
	struct dirent **namelist;
	int ppid = atoi(argv[1]);
	int ans = 1;
	long n = scandir("/proc/", &namelist, NULL, alphasort);
	size_t i;
	ans += filter(namelist, ppid, n);
	for(i = 0; i < n; i++)
	{
		free(namelist[i]);
	}
	free(namelist);
	printf("%d\n", ans);
	return 0;
}

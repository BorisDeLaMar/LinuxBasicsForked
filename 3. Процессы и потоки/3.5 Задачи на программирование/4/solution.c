#include <string.h>
#include <sys/types.h>
#include <dirent.h>  
#include <stdio.h>  
#include <stdlib.h>

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

int filter(const char *name, int ppid)
{
	char *path = malloc(1000*sizeof(char));  
	int ppid_read; int ans = 0; int pid;
	sprintf(path, "%s%s%s", "/proc/", name, "/stat");
	FILE* f = NULL;
	if((f = fopen(path, "r")) == NULL)
	{
		free(path);
	} else
	{
		fscanf(f, "%d", &pid);
		fscanf(f, "%*c %d", &ppid_read);
		if(ppid_read == ppid){
			ans += filter(itoa(pid), );
			free(path);
			fclose(f);
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
	for (i = 0; i < n; i++)
	{
		ans += filter(namelist[i]->d_name, ppid);
		free(namelist[i]);
	}
	free(namelist);
	printf("%d\n", ans);
	return 0;
}

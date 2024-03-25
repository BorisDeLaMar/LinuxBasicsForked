#include <string.h>
#include <sys/types.h>
#include <dirent.h>  
#include <stdio.h>  
#include <stdlib.h>

int filter(const struct dirent *dir)
{
	char *path = malloc(1000*sizeof(char));  
	char *name = malloc(1000*sizeof(char));
	sprintf(path, "%s%s%s", "/proc/", dir->d_name, "/status");
	FILE* f = NULL;
	if((f = fopen(path, "r")) == NULL)
	{
		free(path); free(name);
		return 0;
	} else
	{
		fscanf(f, "%*s %s", name);
		if(strcmp(name, "genenv") == 0){
			free(path); free(name);
			fclose(f);
			return 1;
		} else
		{
			fclose(f);
			free(path); free(name);
			return 0;
		}
	}	
}

int main()
{
	struct dirent **namelist;
	int (*func_filter) (const struct dirent*) = filter;
	long n = scandir("/proc/", &namelist, func_filter, NULL);
	size_t i;
	for (i = 0; i < n; i++)
	{
		free(namelist[i]);
	}
	free(namelist);
	printf("%ld\n", n);
	return 0;
}

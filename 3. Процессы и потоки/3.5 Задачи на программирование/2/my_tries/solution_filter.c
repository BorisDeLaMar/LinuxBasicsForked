#include <string.h>
#include <sys/types.h>
#include <dirent.h>  
#include <stdio.h>  
#include <stdlib.h>

int i = 0;

int filter(const struct dirent *dir)
{
	char *path; char *name;
	printf("Still alive\n");
	sprintf(path, "%s%s%s", "/proc/", dir->d_name, "/status");
	FILE* f = NULL;
	if((f = fopen(path, "r")) == NULL)
	{
		return 0;
	} else
	{
		fscanf(f, "%*s %s", name);
		printf("%s: %s ============= ", path, name);
		i += 1;
		printf("%d", i);
		if(strcmp(name, "genenv") == 0){
			printf("======Hello======\n");
			fclose(f);
			return 1;
		} else
		{
			fclose(f);
			printf(" OMG\n");
			return 0;
		}
	}	
}

int main()
{
	struct dirent **namelist;
	int (*func_filter) (const struct dirent*) = filter;
	long n = scandir("/proc/", &namelist, func_filter, NULL);
	for (i = 0; i < n; i++)
	{
		free(namelist[i]);
	}
	free(namelist);
	printf("%ld\n", n);
	return 0;
}

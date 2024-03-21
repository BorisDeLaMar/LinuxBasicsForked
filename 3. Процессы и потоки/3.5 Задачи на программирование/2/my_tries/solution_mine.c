#include <string.h>
#include <sys/types.h>
#include <dirent.h>  
#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
	struct dirent **namelist;
	char *path = ""; 
	char *pid = ""; 
	FILE* f = NULL; 
	char *name = "";
	int count = 0;
	
	long n = scandir("/proc/", &namelist, NULL, alphasort) - 1;
	while(n)
	{
		pid = namelist[n]->d_name;
		if(isdigit(*pid))
		{
			sprintf(path, "/proc/%s/status", pid); 
			//printf("%s\n", path);
			if(fopen(path, "r") != NULL)
			{
				fscanf(f, "%*s %s", name);
				if(strcmp(name, "genenv") == 0)
				{
					count += 1;			
				}		
				fclose(f);
			}
		}	
		free(namelist[n]);
		n -= 1;
	}
	free(namelist);
	
	printf("%d\n", count);
	
	return 0;
}

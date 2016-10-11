/* ls command --> lists all the files in the current working directory
  */


#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
 
#define FALSE 0
#define TRUE !FALSE

 
extern  int alphasort();
 
 
int main()   { int count,i;
				struct direct **files;
				int file_select();
                 
				char cwd[1024];
                getcwd(cwd, sizeof(cwd));// to get the current working directory
                if(cwd !=NULL){
                 
               printf("Current Working Directory = %s\n",cwd);
				count =scandir(cwd, &files, file_select, alphasort);
 
				if(count>0){
				printf("Number of files = %d\n",count);
				for (i=1;i<count+1;++i)
						 printf("%s  ",files[i-1]->d_name);
				printf("\n"); }
						else{
							printf("No files found");
						}

					}
					else{
						printf("error, can't find the directory");
                

					}
		}



int file_select(struct direct   *entry)
 
		{if ((strcmp(entry->d_name, ".") == 0) ||
						(strcmp(entry->d_name, "..") == 0))
						 return (FALSE);
				else
								return (TRUE);
		}

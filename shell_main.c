#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#define FALSE 0
#define TRUE !FALSE

 
extern  int alphasort();




void ls_command(){

	           int count,i;
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
// file_select is for ls_command
int file_select(struct direct   *entry)
 
		{if ((strcmp(entry->d_name, ".") == 0) ||
						(strcmp(entry->d_name, "..") == 0))
						 return (FALSE);
				else
								return (TRUE);
		}

// time
void curtime(){
time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "Current time and date: %s", asctime (timeinfo) ); // asctime() converts tm structure to string format

}
// rename file and folders
void mv_command(){
    char oldname[100];
    char newname[100];

    printf("Enter old filename: ");
    scanf("%s", oldname);
    printf("Enter new filename:");
    scanf("%s", newname);
    int ret;
   
   
   ret = rename(oldname, newname);
	
   if(ret == 0) 
   {
      printf("File renamed successfully\n");
   }
   else 
   {
      printf("Error: unable to rename the file\n");
   }

}
// remove directory
void remove_dir(){
	 char str[100];
    printf("Enter the directory to delete");
    scanf("%s",str);
    DIR *theFolder = opendir(str);
    struct dirent *next_file;
    char filepath[256];



    while ( (next_file = readdir(theFolder)) != NULL )
    {
        
        sprintf(filepath, "%s/%s", str, next_file->d_name);
        remove(filepath);
        
       
    }
    rmdir(str);
    printf(" Folder Deleted");
    closedir(theFolder);
}
// remove file
void remove_file(){
	int ret;
   
   char filename[100];
   printf("Enter filename to delete: ");
   scanf("%s", filename);
   
   
   ret = remove(filename);

   if(ret == 0) 
   {
      printf("File deleted successfully\n");
   }
   else 
   {
      printf("Error: unable to delete the file\n");
   }
}
// the main function starts
int main(){


int i;

char *arr[8] = {"curtime","ls","cd","refile","delfile","deldir","grep","exit"};// sanjeev you have to add functions of cd and grep 
char *(*ptr)[8] = &arr;
printf("Available commands\n");
for(i=0;i<8;i++)
   printf("%s\n",(*ptr)[i]);


while(1){
		printf(">>");

		char c[10];
		scanf("%s",c);

		int command=0;

		for(i=0;i<8;i++){
				int ret=strcmp(c,(*ptr)[i]);
				if(ret==0){
					
						command=i+1;
						break;

				}
				
		}

		switch(command){
		case 1: curtime();
		break;
		case 2:ls_command();
		break;
		case 3://cd function
		break;
		case 4:mv_command();
		break;
		case 5:remove_file();
		break;
		case 6:remove_dir();
		break;
		case 7://grep function
		break;
		case 8: exit(0);
		default: printf("Command Not Found\n");
		break;

		}

}
return 0;


}

#include <stdio.h>

int main ()
{   
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
   
   return(0);
}
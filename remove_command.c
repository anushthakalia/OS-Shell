#include <stdio.h>
#include <string.h>

int main ()
{
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
   
   return(0);
}
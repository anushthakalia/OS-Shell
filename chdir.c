#include <stdio.h>
#include <unistd.h>

void change_directory(char *path);

int main()
{    
    change_directory("/home/sanjeev/Operating_System_Coding/Shell development/sanjeev");
    // function needs a string of path directory.
}

void change_directory(char *path)
{
    int status = chdir(path);
    printf("%c", status);
    if (0==status)   printf("Directory changed to: %s \n", path);
    else  printf("%s\n", "Error: no directory found" );
}
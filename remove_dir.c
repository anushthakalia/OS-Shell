#include <stdio.h>
#include <dirent.h>
//This works only for those folders whose contents are  files
int main()
{
    // These are data types defined in the "dirent" header
    char str[100];
    printf("Enter the directory to delete");
    scanf("%s",str);
    DIR *theFolder = opendir(str);
    struct dirent *next_file;
    char filepath[256];
    getcwd(filepath, sizeof(filepath));


    while ( (next_file = readdir(theFolder)) != NULL )
    {
        // build the path for each file in the folder
        sprintf(filepath, "%s/%s", str, next_file->d_name);
        remove(filepath);
        
       
    }
    rmdir(str);
    printf(" Folder Deleted");
    closedir(theFolder);
    return 0;
}

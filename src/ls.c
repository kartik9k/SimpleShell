#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    DIR *mydir;
    struct dirent *myfile;
    int optional_flag = 0;
    int all_flag = 0;
    int l_flag = 0;

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    if (argv[1] != NULL){
        char *temp = argv[1];
        if (temp[0] == '-'){
            optional_flag = 1;
            if (temp[1] == 'a')
                all_flag = 1;
            // else if (temp[1] == 'l')
            //     l_flag = 1;
        }

        else{
            mydir = opendir(argv[1]);
        }
    }

    else{
        mydir = opendir(cwd);
    }

    if (optional_flag){
        if (argv[2] != NULL)
            mydir = opendir(argv[2]);
        else
            mydir = opendir(cwd);
    }

    if (mydir == NULL){
        printf("Directory could not be opened\n");
        return 1;
    }

    while((myfile = readdir(mydir)) != NULL){
        if (all_flag){
            printf("%s ", myfile -> d_name);
        }

        else {
            char *temp = (myfile -> d_name);
            if (temp[0] != '.')
                printf("%s ", myfile -> d_name);
        }

        // else if (l_flag){
        //     printf("%s\n", );
        // }


    }
    printf("\n");
    closedir(mydir);
}
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if (argv[1] == NULL){
		printf("No file mentioned\n");
		return 1;
	}
	char cwd[1024];
	char f_name[1024];
	getcwd(cwd, sizeof(cwd));
	char *temp = argv[1];
	if (temp[0] != '-'){
		int i = 1;
		while (argv[i] != NULL){
			strcat(cwd, "/");
			strcat(cwd, argv[i]);
			strcpy(f_name, cwd);
			int ret = remove(f_name);
			if (ret == 0)
				printf("Deleted %s succesfully.\n", argv[i]);
			else
				printf("Error: Unable to delete\n");
			i += 1;
		}
	}	
}
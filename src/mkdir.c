#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	if (argv[1] == NULL){
		printf("Directory not mentioned.\n");
		return 1;
	}

	if (mkdir(argv[1], ACCESSPERMS) != 0)
		printf("Directory could not be created.\n");
	return 1;
}
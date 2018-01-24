#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	if (argv[1] == NULL){
		printf("No file mentioned\n");
		return 1;
	}

	FILE *f = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int num_line = 0;
	int next_line_dolla = 0;

	char *temp = argv[1];
	if (temp[0] != '-'){
		f = fopen(argv[1], "r");
	}

	else{
		if (temp[1] == 'n')
			num_line = 1;
		else if (temp[1] == 'b')
			next_line_dolla = 1;

		if (argv[2] != NULL)
			f = fopen(argv[2], "r");
		else{
			printf("No file mentioned\n");
			return 1;
		}
	}

	int i = 1;

	if (f){
		read = getline(&line, &len, f);
		while(read != -1){
			if (num_line){
				printf("%d  %s", i, line);
				i += 1;
			}

			else if (next_line_dolla)
				if (line[0] != '\n'){
					printf("%d %s",i, line);
					i += 1;
				}
				else
					printf("%s", line);
			else
				printf("%s", line);
			read = getline(&line, &len, f);
		}
		printf("\n");
	fclose(f);
	}

	else{
		printf("File could not be opened\n");
		return 1;
	}
}
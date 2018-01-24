#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int ush_cd(char **args){
	if (args[1] != NULL){
		int status = chdir(args[1]);
		if (status != 0)
			fprintf(stderr, "Invalid directory.\n");
	}

	else{
		fprintf(stderr, "Please enter a path\n");
	}

	return 1;
}

int ush_exit(char **args){
	exit(0);
	return 1;
}

int ush_echo(char **args){
	int i = 1;
	int one = 0;
	int no_new_line = 0;
	int enable_backslash = 0;

	while (args[i]){
		char *temp = args[i];
		if (i == 1 || (one && i == 2)){
			if (temp[0] == '-'){
				if (temp[1] == 'n' && !temp[2]){
					no_new_line = 1;
					one = 1;
				}
				else if (temp[1] == 'e' && !temp[2]){
					enable_backslash = 1;			
					one = 1;
				}
			}
		}
		
		i += 1;
	}
	// printf("nl = %d, bl = %d\n", no_new_line, enable_backslash);
	if (!enable_backslash && !no_new_line)
		i = 1;
	else if ((!enable_backslash && no_new_line) || (!no_new_line && enable_backslash))
		i = 2;
	else
		i = 3;

	if (!enable_backslash){
		if (args[i]){
			char *temp = args[i];
			int j = 0;
			while (temp[j]){
				if (temp[j] != '\"')
					printf("%c", temp[j]);
				j += 1;
			}
		}
		
		i += 1;
		while (args[i]){
			char *temp = args[i];
			
			printf(" ");
			int j = 0;
			while (temp[j]){
				if (temp[j] != '\"')
					printf("%c", temp[j]);
				j += 1;
			}
			
			i += 1;
		}
		if (!no_new_line)
			printf("\n");
	}

	else{
		if (args[i]){
			char *temp = args[i];
			int j = 0;
			while (temp[j]){
				if (temp[j] != '\"'){
					if (temp[j] != '\\')
						printf("%c", temp[j]);
					else{
						if (temp[j + 1]){
							int no_flag = 0;
							if (temp[j + 1] == 'n')
								printf("\n");
							else if (temp[j + 1] == '\\')
								printf("\\");
							else if (temp[j + 1] == 't')
								printf("    ");
							else if (temp[j + 1] == 'c')
								return 1;
							else
								no_flag = 1;

							if (!no_flag)
								j += 1;
							else
								printf("%c", temp[j]);
						}
					}
				}

				j += 1;
			}	
		}

		i += 1;
		while (args[i]){
			char *temp = args[i];
			int j = 0;
			while (temp[j]){
				if (temp[j] != '\"'){
					if (temp[j] != '\\')
						printf("%c", temp[j]);
					else{
						if (temp[j + 1]){
							int no_flag = 0;
							if (temp[j + 1] == 'n')
								printf("\n");
							else if (temp[j + 1] == '\\')
								printf("\\");
							else if (temp[j + 1] == 't')
								printf("    ");
							else if (temp[j + 1] == 'c')
								return 1;
							else
								no_flag = 1;

							if (!no_flag)
								j += 1;
							else
								printf("%c", temp[j]);
						}
					}
				}

				j += 1;
			}
		i += 1;	
		}

		if (!no_new_line)
			printf("\n");
	}
	return 1;
}

int ush_pwd(char **args){
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
	return 1;
}

int ush_history(char **args){
	FILE *f = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	f = fopen("history.txt", "r");
	if (f){
		read = getline(&line, &len, f);
		while(read != -1){
			printf("%s", line);
			read = getline(&line, &len, f);
		}
		printf("\n");
	fclose(f);
	}

}

void add_to_history(char *command){
	FILE *f = NULL;

	f = fopen("history.txt", "a");
	if (f){
		fprintf(f, "%s\n", command);
		fclose(f);
	}
}

char *builtins[] = {"cd", "exit", "echo", "pwd", "history"};
int (*builtin_function[]) (char **) = {&ush_cd, &ush_exit, &ush_echo, &ush_pwd, &ush_history};

int run_builtin_commands(char **arguments){
	int i;
    int builtins_size = sizeof(builtins) / sizeof(char *);
    for (i = 0; i < builtins_size; i++){
    	if (strcmp(arguments[0], builtins[i]) == 0){
    		(*builtin_function[i])(arguments);
    		return 1;
    	}
    }
    return 0;
}

int main(void){
	char *arguments[100];
	char cwd[1024];
	
	getcwd(cwd, sizeof(cwd));
	strcat(cwd, "/bin/");

	char path[1024];
	strcpy(path, cwd);
	char program_path[20];

	while(1){
		printf("ush> ");
		char *command = NULL;
		ssize_t bufsize = 0; 
  		getline(&command, &bufsize, stdin);

  		char *temp = command;
  		while (*command != '\n')
  			command += 1;

  		*command = '\0';
  		command = temp;

		char *token = strtok(command, " ");
   
   		int i = 0;
	    while (token != NULL){
	        arguments[i] = token;
	        token = strtok(NULL, " ");
	        i += 1;
	    }
	    arguments[i] = NULL;

	    if (run_builtin_commands(arguments) == 1){
	    	add_to_history(command);
	    	continue;
	    }
	    
	    else{
		    strcpy(program_path, path);
		    strcat(program_path, arguments[0]);
		    int flag = 0;

		    int pid = fork();
		    pid_t wpid;
		    int status;

		    if (pid == 0){
		    	if(execvp(program_path, arguments) == -1){
		    		fprintf(stderr, "%s: command not found\n", arguments[0]);
		    		flag = 1;
		    		break;
		    	}		    	
		    }

		    else if (pid > 0){
		    	wpid = waitpid(pid, &status, WUNTRACED);
		    	while (!WIFEXITED(status) && !WIFSIGNALED(status)){
			    	wpid = waitpid(pid, &status, WUNTRACED);
		    	}
		    }

		    else{
		    	perror("ush");
		    }

			add_to_history(command);
	    }

	}
}
all: ush.c ls.c
	mkdir bin
	gcc -g -o ush ush.c 
	gcc -g -o bin/ls ls.c
	gcc -g -o bin/cat cat.c
	gcc -g -o bin/date date.c  
	gcc -g -o bin/rm rm.c  
	gcc -g -o bin/mkdir mkdir.c  

	gnome-terminal -e ./ush

clean:
	rm -rf ush history.txt bin
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]){
	time_t t;
	time(&t);

	printf("%s", ctime(&t));
}
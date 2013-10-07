#include <stdio.h>
#include <stdlib.h>

/* use gprof */
/* see: http://www.cs.utah.edu/dept/old/texinfo/as/gprof.html */

void usage(char * program_name) {
	fprintf(stderr, "usage: %s n [arg0] [arg1] ...\n",program_name);
	exit(0);
}

int foo(int x, int y);
int bar(int x, int y);

int main(int argc, char ** argv) {
	int i, j, n, t;
	int x = 0;
	int xa;

	if (argc < 2)
		usage(argv[0]);

	n = atoi(argv[1]);
	t = n/100;

	printf("foo:\n");
	for(i=2; i<argc; i++) {
		xa = atoi(argv[i]);
		for(j=0; j<n; j++) {
			x = foo(j,xa);
			if(j % t == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf("\n");
	}

	printf("bar:\n");
	for(i=2; i<argc; i++) {
		xa = atoi(argv[i]);
		for(j=0; j<n; j++) {
			x = bar(j,xa);
			if(j % t == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf("\n");
	}

	return 0;
}

int foo(int x, int y) {
	int i;
	int z = 0;
	for(i=0; i<x; i++)
		z = ((i+y)*i)%(i+1);
	return z;
}

int bar(int x, int y) {
	int i;
	int z = 0;
	for(i=0; i<x; i++)
		z = (i*i)%(i+1+y);
	return z;

}

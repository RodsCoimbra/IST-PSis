#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
/* include the correct .h file */

int main(){
	int a;
	char line[100];
	char library_name[100];

	printf("What version of the functions you whant to use?\n");
	printf("\t1 - Normal    (lib1)\n");
	printf("\t2 - Optimized (lib2)\n");
	fgets(line, 100, stdin);
	sscanf(line,"%d", &a);
	if (a == 1){
		strcpy(library_name, "./lib1.so");
		printf("running the normal versions from %s \n", library_name);
	}else{
		if(a== 2){
			strcpy(library_name, "./lib2.so");
			printf("running the normal versions %s \n", library_name);
		}else{
			printf("Not running anything\n");
			exit(-1);
		}
	}
	/* load library from name library_name */
	void *handle;
	handle = dlopen(library_name, RTLD_LAZY);

	/* declare pointers to functions */
	void (*pfunc1)();
	void (*pfunc2)();
	/*load func_1 from loaded library */
	pfunc1 = dlsym(handle, "func_1");
	/*load func_2 from loaded library */
	pfunc2 = dlsym(handle, "func_2");
	/* call func_1 from whichever library was loaded */
	pfunc1();
	/* call func_2 from whichever library was loaded */
	pfunc2();
	dlclose(handle);
	exit(0);
}

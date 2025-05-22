// C program to demonstrate working of fork()
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

int globalVar = 0; // A global variable

int main(void)
{
	// local variable
	int localVar = 0;

	int* privateMem = (int*)mmap(
		NULL, sizeof(int), PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	int* sharedMem = (int*)mmap(
		NULL, sizeof(int), PROT_READ | PROT_WRITE,
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	pid_t childPID = fork();

	// Putting value at allocated address
	*privateMem = 0;
	*sharedMem = 0;

	if (childPID < 0) // fork was unsuccessful
	{
		printf("\n Fork failed, quitting!!!!!!\n");
		return 1;
	}

	if (childPID == 0) // child process
	{
		printf("\n Child Process Initial Value :: localVar"
			" = %d, globalVar = %d",
			localVar, globalVar);

		printf("\n Address of malloced privateMem in child "
			"= %p "
			"and value is %d",
			privateMem, *privateMem);
		printf("\n Address of malloced sharedMem in child "
			"= %p "
			"and value is %d",
			sharedMem, *sharedMem);

		localVar = 1;
		globalVar = 2;

		printf("\n Updated child Process :: localVar = %d, "
			"globalVar = %d",
			localVar, globalVar);

		printf("\n lets change the value of privateMem "
			"variable "
			"created by malloc in child");
		*privateMem = 50;
		printf("\n Address of malloced privateMem in child "
			"= %p "
			"and value is %d",
			privateMem, *privateMem);

		printf("\n lets change the value of sharedMem "
			"variable "
			"created my malloc in child");
		*sharedMem = 100;
		printf("\n Address of malloced sharedMem in child "
			"= %p "
			"and value is %d\n\n",
			sharedMem, *sharedMem);

		exit(EXIT_SUCCESS);
	}
	else {
		wait(NULL); // Wait for child process to exit

		printf("\n Parent Process Initial Value :: "
			"localVar = %d, globalVar = %d",
			localVar, globalVar);

		printf("\n Address of malloced privateMem in "
			"parent = %p "
			"and value is %d",
			privateMem, *privateMem);
		printf("\n Address of malloced sharedMem in parent "
			"= %p "
			"and value is %d",
			sharedMem, *sharedMem);

		localVar = 10;
		globalVar = 20;
		printf("\n Updated parent process :: localVar = %d,"
			" globalVar = %d",
			localVar, globalVar);

		printf("\n lets change the value of privateMem "
			"variable "
			"created by malloc in parent");
		*privateMem = 100;
		printf("\n Address of malloced privateMem in "
			"parent= %p "
			"and value is %d",
			privateMem, *privateMem);

		printf("\n lets change the value of sharedMem "
			"variable "
			"created my malloc in parent");
		*sharedMem = 400;
		printf("\n Address of malloced sharedMem in parent "
			"= %p"
			" and value is %d \n",
			sharedMem, *sharedMem);
	}

	return 0;
}


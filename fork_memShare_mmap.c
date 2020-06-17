/*Program to demonstrate shared memory creation using 
'mmap' --> creates new mapping in the virtual address space of the calling process 

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

Memory is sharable b/w parent and child , both of them can modify memory. 
*/ 


#include<stdio.h> 

#include<stdlib.h> 

#include<sys/types.h> 
#include<unistd.h> 

#include<sys/wait.h> 

#include<sys/mman.h>

#include<string.h> 

#define CHILD 0 

int main(int argc, char **argv)
{
	 
	int childstatus, size = 1024, fd = -1; 
	char *area;	
	pid_t pid;
	
	printf("Start of funtion \n"); 

	area = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, fd, 0); 
	pid = fork();  

	if(pid == CHILD) {
		strcpy(area, "This is a Message from Child");
		printf("Reading memory from child : %s \n", area); 
		exit(EXIT_SUCCESS);
	}
	else {
		wait(&childstatus);
		printf("Reading memory from parent : %s \n", area); 
		exit(EXIT_SUCCESS); 
	}

	exit(EXIT_FAILURE);
}

/*Output : 
Start of funtion
Reading memory form child : This is a Message from Child
Reading memory from parent : This is a Message from Child 
*/

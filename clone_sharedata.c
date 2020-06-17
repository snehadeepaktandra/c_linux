/*Program shows clone funtion call and share data b/w parent and child 
i. share variables 
ii. share open files 
*/ 

#define _GNU_SOURCE
#include<sched.h>

#include<stdio.h>

#include<stdlib.h> 

//header for sleep funtion
#include<unistd.h>

#include<fcntl.h>

#define STACK_SIZE 1024 

//#define SHARE_DATA
#define SHARE_FILE

int fd; 

int child_funtion(void *arg) 
{

#ifdef SHARE_DATA
	printf("Control in child process and modifying variable \n " );
	*(int *)arg = 40; 
	printf("variable in child : %d \n", *(int *)arg);

#endif 

#ifdef SHARE_FILE
	printf("Control in child process and modifying variable \n " );
	close(fd);

#endif 

}

int main()
{

#ifdef SHARE_DATA
	void *child_stack_ptr; 	
	int variable = 10; 
	printf("Printing variable at start of execution : %d \n", variable);  
	
	child_stack_ptr = malloc(STACK_SIZE); 
	if(child_stack_ptr == NULL ) {
		perror("Child stack creation failed \n"); 
		exit(1);
	}
	clone(child_funtion, child_stack_ptr+STACK_SIZE, CLONE_VM | CLONE_FILES, &variable);
	//waiting for child to update 
	sleep(2); 
	printf("Printing variable at the end from parent : %d \n", variable ); 
	

#endif 

#ifdef SHARE_FILE
	void *child_stack_ptr;
	char buf[2];  	
	int ret; 

	fd = open("test.txt", O_RDWR); 
	
	child_stack_ptr = malloc(STACK_SIZE); 
	if(child_stack_ptr == NULL ) {
		perror("Child stack creation failed \n"); 
		exit(1);
	}
	clone(child_funtion, child_stack_ptr+STACK_SIZE, CLONE_VM | CLONE_FILES, NULL);
	//waiting for child to update 
	sleep(2); 
	ret = read(fd, buf, 2); 
	printf("ret val : %d \n", ret); 
	if(ret < 0) {
		perror("read error"); 
		exit(1);  
	}
	
#endif 

}

/*Output : 
SHARE_DATA --> 
Printing variable at start of execution : 10 
Control in child process and modifying variable 
 variable in child : 40 
Printing variable at the end from parent : 40

SHARE_FILE --> 
(gdb) r
Starting program: /home/deepakubuntu/workspace/c_sample_programs/local_ws/a.out 
[New LWP 2439]
Control in child process and modifying variable 
[LWP 2439 exited]
 ret val : -1 
read error: Bad file descriptor
[Inferior 1 (process 2435) exited with code 01]
(gdb) 
*/ 

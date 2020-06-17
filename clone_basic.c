/*Program to demonstrate basic clone funtion call for thread creation 
       int clone(int (*fn)(void *), void *child_stack,
                 int flags, void *arg, ...
	
	first argument : Name of funtion which will run as child 
	second argument : stack space provided to child for its own execution 
	Third argument : flags to device what attributes to be shared and what attributes to be made private 
		CLONE_VM -> memory region used is same b/w both parent and child 
		CLONE_FILES -> file descriptors used any are shared bw both parent and child 
	fourth argument : parameters to be passed to child funtion while calling 

*/ 

//for clone and it's respective flags 
#define _GNU_SOURCE
#include<sched.h>

#include<stdio.h> 
#include<stdlib.h> 


#define STACK_SIZE 1024

int child_funtion(void *arg) {
	
	printf("Control in Child funtion \n") ;
	getchar(); 

	}


int main()
{
	
	void *child_stack_ptr;
	/*acquire memory for child stack*/  
	child_stack_ptr = malloc(STACK_SIZE); 

	if(child_stack_ptr == NULL) {

		perror( "Error Creating \n "); 
		exit(1); 
	}

	clone(child_funtion, child_stack_ptr+STACK_SIZE, CLONE_VM | CLONE_FILES, NULL ); 
	getchar(); 
	printf("Parent process \n");

}

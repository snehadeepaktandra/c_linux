/* This program is to demonstrate fork() usage and how does thread creation work using fork funtion call */ 

//headers for fork() 
#include<sys/types.h> 
#include<unistd.h> 

#include<stdio.h>

#define CHILD 0 

#if 0 
//simple demonstration : 

int main() 
{
	pid_t pid; 
	printf("Start of program \n"); 
 
	pid = fork(); 
	
	printf("pid of current process : %d \n" , getpid() ); 
	printf("child pid is : %d \n", pid); 

	return 0; 

} 

Output : 
Start of program 
pid of current process : 3813 
child pid is : 3814 
pid of current process : 3814 
child pid is : 0 

#endif

#if 1
//termination of parent task still allows child to run, can be understood with executing below piece of code. check using pid's (ps -Af)  
//both the processes are running independently.  
//child is drivern by init thread if parent terminates. 

int main() 
{
	pid_t pid; 
	printf("Start of program \n"); 

	pid = fork(); 
	printf("Current pid : %d \n", getpid());
//	getchar(); 

	if(pid == CHILD)  {
		//child 
		printf("child -> my pid is : %d \n", getpid() );   
		while(1);
	} 
	else {
		//parent 
//		getchar(); 	
		printf("parent -> my pid is : %d \n", getpid() ); 
		printf("parent -> my child pid is : %d \n", pid ); 
	}

return 0; 
}

//adding infinite loop in parent thread shows child doesn't end if parent doesn't reach exit state.  

#endif 

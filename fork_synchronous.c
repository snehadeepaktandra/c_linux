//synchronous mode - parent is put into wait state until child terminates. 

#include<stdio.h> 

//for fork()
#include<sys/types.h> 
#include<unistd.h> 

//for wait()
#include<sys/wait.h>

//for exit()
#include<stdlib.h>

#define CHILD 0 


int main() 
{

	pid_t pid; 
	int k = 20; 
	int childstatus ; 

	printf("start of funtion \n") ; 

	printf("current pid : %d \n", getpid() ); 
	pid = fork(); 

	if(pid == CHILD)  {
		//child 
		printf("child --> my pid is : %d \n", getpid() ); 
		printf("child --> value of k before modifying : %d \n", k );  
		k = 400; 
		printf("child --> value of k after modifying : %d \n ", k ); 
		printf("child --> end  \n"); 
		exit(100);
	}
	else {
		//parent 
		printf("parent --> my pid is : %d \n", getpid() ); 
		printf("parent --> my child pid is : %d \n", pid ); 
		printf("parent --> value of k : %d \n ", k); 
		wait(&childstatus);  
		printf("parent --> child status : %d \n ", WEXITSTATUS(childstatus));
		printf("parent --> end \n");   

	}
return 0; 

}

/*Output : 
start of funtion 
current pid : 7918 
parent --> my pid is : 7918 
parent --> my child pid is : 7919 
parent --> value of k : 20 
child --> my pid is : 7919 
child --> value of k before modifying : 20 
child --> value of k after modifying : 400 
 child --> end  
 parent --> child status : 100 
 parent --> end
*/ 

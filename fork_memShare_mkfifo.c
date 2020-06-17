/*Program to demonstrate shared memory creation using 
'mkfifo' --> make FIFOs (named pipes) 

Memory is sharable b/w parent and child , both of them can modify memory. 
*/

#include<stdio.h> 

#include<stdlib.h> 

#include<sys/types.h> 
#include<unistd.h> 

#include<sys/wait.h> 

#include<sys/stat.h>

#include<fcntl.h> 

#include<errno.h>


#define DEATH(mess) {perror(mess); exit(errno); }
#define CHILD 0  

#define FIFO_NAME "./myfifo" 

int main(int argc, char *argv[]) 
{


	pid_t pid; 
	int fd; 
	char message[] = "Hello world on FIFO"; 	

	printf("start of Funtion \n"); 
	
	if(mkfifo(FIFO_NAME, 0666) < 0)  {
		DEATH(FIFO_NAME); 
	} 	
	printf("File created : %s \n", FIFO_NAME); 
	fflush(stdout); 

	pid = fork();  

	if(pid == CHILD) {	/*child*/
		fd = open(FIFO_NAME, O_WRONLY); 
		printf("Child writing message to FIFO is : %s \n", message);		
	
		if(write(fd, message, sizeof(message)) < 0) {
			DEATH("write error from child to FIFO"); 
		}
		close(fd);
		exit(EXIT_SUCCESS); 
	}
	if(pid > 0 ) {		/*Parent*/ 
		fd = open(FIFO_NAME, O_RDONLY); 
		if (read(fd, message, sizeof(message) < 0 ) ) {
			DEATH("Read error from parent to FIFO") ; 		
		}
		printf("Parent reading message from FIFO is : %s \n", message); 
		close(fd); 

		if(unlink(FIFO_NAME))
			DEATH("Trouble removing FIFO"); 

		exit(EXIT_SUCCESS);  

	}

	DEATH("Fork"); 


}

/*Output : 
start of Funtion 
File created : ./myfifo 
Parent reading message from FIFO is : Hello world on FIFO 
Child writing message to FIFO is : Hello world on FIFO 
*/ 

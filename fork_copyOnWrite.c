//program to understand how copy on write works for shared variables b/w parent and child threads 

#include<stdio.h> 

#include<unistd.h> 
#include<sys/types.h>
#include<sys/wait.h> 

#include<fcntl.h> 

#define CHILD 0 

int main()
{

	int fd; 
	pid_t pid; 
	int childstatus; 
	char buf[2]; 
 
	printf("start of funtion \n"); 

	fd = open("./test.txt", O_RDONLY);   
	pid = fork(); 

	if(pid == CHILD) {	/*child*/ 
		read(fd, buf, 2);
		printf("child --> %c \n", buf[0]);
		printf("child --> %c \n", buf[1]);
		close(fd); 		

	}
	else {			/*parent*/
		wait(&childstatus); 
		read(fd, buf, 2);
		printf("parent --> %c \n", buf[0]);
		printf("parent --> %c \n", buf[1]);
		close(fd); 
	}

return 0; 

}

/*output : 
start of funtion 
child --> a 
child --> b 
parent --> c 
parent --> d
*/ 

/* 
test.txt : abcdefghi
Inferences : 
1. close fd in child creates one more copy of fd for child. But the original one is incremented with read. Hence parents reads 'c' and 'd'
*/ 


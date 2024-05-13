//Assignment 2 :- From a parent process (A) create a child process (B). The child (B) in turn creates new child process (C) and it (C) in turn create new child (D). All these
//processes should run concurrently for 5 seconds and cleaned up properly upon termination.

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void){
	int ret1,ret2,ret3,s1,s2,s3;
	ret1 = fork();
	sleep(1);
	if(ret1 == 0){
		ret2 = fork();
		if(ret2 == 0){
			ret3 = fork();
			if(ret3 == 0){
				printf("Child_D is child of child_C\n");
				printf("Child of %d is %d\n",getppid(),getpid());
				_exit(1);
			}
				printf("Child_C is child of child_B\n");
			printf("Child of %d is %d \n",getppid(),getpid());
			waitpid(ret3,&s1,0);
			_exit(1);
		}
				printf("Child_B is main child\n");
		printf("Child of %d is %d \n",getppid(),getpid());
		waitpid(ret2,&s2,0);
			_exit(1);
	}
	printf("Parent A : %d \n",getpid());
	waitpid(ret1,&s3,0);

}

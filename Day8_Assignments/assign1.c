//ONE PARENT - Three child processes

#include <unistd.h>
#include <stdio.h>

int main () 
{
   int ret1, ret2, ret3, ret4, ret5, i, s;
   char child_pid;
   ret1 = fork();
   if(ret1 == 0) {
         for(i=1; i<=5; i++) {
			printf("child1: %d\n", i);  //child 1
			printf("child1: pid=%d\n", getpid());
			sleep(1);
         }
	_exit(0);	 
   }		 
   ret2 = fork();
   if(ret2 == 0) {
           for(i=1; i<=5; i++) {
              printf("child2: %d\n", i);  //child 2
			  printf("child2: pid=%d\n", getpid());
              sleep(1);
           }
     _exit(0);
    }
	ret3 = fork();
    if(ret3 == 0) {
           for(i=1; i<=5; i++) {
              printf("child3: %d\n", i);  //child 3
			  printf("child3: pid=%d\n", getpid());
              sleep(1);
           }
	 _exit(0);
     }
	 ret4 = fork();
     if(ret4 == 0) {
             for(i=1; i<=5; i++) {
                printf("child4: %d\n", i);  //child 4
				printf("child4: pid=%d\n", getpid());
                sleep(1);
            }
       _exit(0);
	   }
	  ret5 = fork();
      if(ret5 == 0) {
             for(i=1; i<=5; i++) {
                printf("child5: %d\n", i);  //child 5
				printf("child5: pid=%d\n", getpid());
                sleep(1);
             }
       _exit(0);
      }

    else {
		// parent process
		for(i=1; i<=5; i++) {
			child_pid = wait(&s);
			printf("parent: %d\n", i);
			sleep(1);
		}
	}
	return 0;
}




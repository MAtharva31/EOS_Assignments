#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

 void sigint_handler(int sig){
 	printf("SIGINT Handler : %d\n", sig);
}

int main(){

		char cmd[512], *ptr, *args[32];
		int ret, i, s, err;

    	signal(SIGINT, sigint_handler);

		printf("Program Started..\n");

		while(1){
			printf("cmd> ");
            gets(cmd);
			i=0;

			ptr = strtok(cmd," ");
			args[i] = ptr;
			i++;

			do{
				ptr = strtok(NULL, " ");
				args[i] = ptr;
				i++;
			}while(ptr != NULL);

			if(strcmp(args[0],"Exit") == 0){
				break;
			}
			else if(strcmp(args[0],"cd")==0){
				chdir(args[1]);
			}
			else {
			ret = fork();
			if(ret == 0) {
				err = execvp(args[0], args);
				if(err < 0) {
					perror("bad command");
					_exit(1);
				}
			}
			else
				wait(&s);
		}
	}
	printf("bye!\n");
	return 0;
}

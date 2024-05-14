#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void){
	int ;
	ret1 = fork();
	sleep(1);
	if(ret1 == 0){
		ret2 = fork();
		if(ret2 == 0){
			ret3 = fork();
			if(ret3 == 0){
				

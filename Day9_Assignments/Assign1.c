#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>

int main(){
	int ret,pid,sig_num;
	
	printf("Enter the Pid : ");
	scanf("%d",&pid);

	printf("Enter the Signal Number : ");
	scanf("%d",&sig_num);

	ret = kill(pid,sig_num);

	if(ret == 0){
		printf("Process killed successfully..!");
	}
	else{
		perror("Kill failed..!!");
		_exit(1);
	}
	return 0;
}

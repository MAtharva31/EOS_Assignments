#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
int main()
{
	int ret,arr1[2],arr2[2];
	int num1,num2,res,s;
	ret = pipe(arr1);
	ret = pipe(arr2);
	if(ret < 0)
	{
	perror("pipe() failed");
	_exit(1);
	}
	ret = fork();

	if(ret == 0)
	{
	printf("child process running\n");
	close(arr1[0]);
	close(arr2[1]);
	printf("enter two numbers:\n");
	scanf("%d", &num1);
	scanf("%d", &num2);

	write(arr1[1],&num1,sizeof(num1));
	write(arr1[1],&num2,sizeof(num2));
	
	read(arr2[0],&res,sizeof(res));
	printf("result :%d\n",res);

	close(arr2[0]);
	close(arr2[1]);
	}
	else{
	printf("parent process running\n");
	close(arr1[1]);
	close(arr2[0]);
	read(arr1[0],&num1,sizeof(num1));
	read(arr1[0],&num2,sizeof(num2));
	res = num1+num2;
	write(arr2[1],&res,sizeof(res));

	close(arr2[1]);
	close(arr2[0]);
	waitpid(-1,&s,0);
	}

	return 0;
}

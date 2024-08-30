#include "../sources/pipex.h"
#include <sys/wait.h>


/* int main(){

	int fd[2];

	if(pipe(fd) == -1){
		printf("\nError: Could not create a pipe!\n");
		exit(-1);
	}

	int cpid = fork();

	if(cpid == -1){
		printf("\nError: Could not fork!\n");
		exit(-1);
	}

	if(cpid == 0){
		char toSend[] = "Hello educative user! <3";
		write(fd[1], toSend, strlen(toSend));
		printf("\nChild: Data sent to parent!\n");
		exit(0);
	}
	else{
		wait(NULL);
		char toRecieve[BUFSIZ];
		read(fd[0], toRecieve, BUFSIZ);
		printf("\nParent: Data from child = %s\n\n", toRecieve);
		exit(0);
	}
} */

/*
//Testar dup(int oldfd) e o dup2(int oldfd, int newdf)
int main(int argc, char **argv)
{
	(void)argc;
	if(errors(argv[1]) == -1)
		return (ft_putstr_fd("Error\n", 2), 0);
	int fd = open("text.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, "Texto original.\n", 16);
	printf("fd %d\n", fd);
	write(fd, "Texto duplicado usando dup().\n", 30);
	printf("fd_dup %d\n", fd);
	int fd_dup2 = dup2(fd, 10);
	write(fd_dup2, "Texto duplicado usando dup2().\n", 31);
	printf("fd_dup2 %d\n", fd_dup2);
	close(fd);
	close(fd_dup2);

	return 0;
} */

//Testar execve()
/* int main()
{
		char *shell = "/bin/sh";
		char *args[] = {"/bin/sh", NULL};
		char *env[] = {NULL};
		execve(shell, args, env);
} */

//Fork tests
/*int main() 
{ 
   	int a = fork();
	int b = fork();
	int c = fork();

	printf("pid %d a %d b %d c %d\n", getpid(), a, b, c);
	return 0; 
}*/

/* void forkexample() 
{ 
	int x = 1; 
	pid_t p = fork(); 
	  if(p<0){ 
	  perror("fork fail"); 
	  exit(1); 
	} 
	else if (p == 0) 
		printf("Child has x = %d\n", ++x); 
	else 
		printf("Parent has x = %d\n", --x); 
} 
int main() 
{ 
	forkexample(); 
	return 0; 
}  */

//Pipe tests

/*int main() 
{
	char* msg1 = "hello, world #1"; 
	char* msg2 = "hello, world #2"; 
	char* msg3 = "hello, world #3"; 
	char inbuf[16]; 
	int p[2], i; 
  
	if (pipe(p) < 0) 
		exit(1); 
  
	//continued
	//write pipe
  
	write(p[1], msg1, 16); 
	write(p[1], msg2, 16); 
	write(p[1], msg3, 16); 
  
	for (i = 0; i < 3; i++) { 
		// read pipe 
		read(p[0], inbuf, 16); 
		printf("%s\n", inbuf); 
	} 
   return 0; 
}*/

//Testing pipe, and tranfering strings to the fd
/* int main (int argc,char **argv)
{
	(void) argc;
    int fd[2];
    int fd2 = open(argv[4], O_WRONLY); 
	if(pipe(fd) == -1){
        printf("\nError: Could not create a pipe!\n");
        exit(-1);
    }

    int cpid = fork();

    if(cpid == -1){
        printf("\nError: Could not fork!\n");
        exit(-1);
    }

    if(cpid == 0){
        char toSend[] = "Hello educative user! <3";
        write(fd[1], toSend, strlen(toSend));
        printf("\nChild: Data sent to parent!\n");
        exit(0);
    }
    else{
        wait(NULL);
        char toRecieve[BUFSIZ];
        read(fd[0], toRecieve, BUFSIZ);
	write(3, &toRecieve, ft_strlen(toRecieve));
        printf("\n  Parent: Data from child = %s\n\n", toRecieve);
        exit(0);
    }
	close(fd2);
	return 0;
} */

/*Tests execve() function with ls -l command
int main() {
    // The full path to the "ls" executable
	char *path = "/bin/ls";
    
    // Arguments for the "ls" command; the first argument must be the command itself
    char *args[] = {"ls", "-l", NULL};  // `ls -l` command

    // Environment variables; NULL means inherit the current environment
    char *env[] = {NULL};  
    
    // Execute the "ls" command
    if (execve(path, args, env) == -1) {
        perror("execve");  // If execve returns, it must have failed
        exit(EXIT_FAILURE);
    }

    return 0;  // This line will not be executed if execve is successful
}*/

//Testing envp
int main (int argc, char **argv, char **envp)
{
	int i = 0;
	while(envp[i])
	{
		printf("argv[%d] %s     envp[%d] %s\n", i, argv[i], i, envp[i]);
	}
}
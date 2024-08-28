#include "pipex.h"

/*static int errors(char *file)
{
	if(access(file, R_OK) == -1 || access(file, F_OK) == -1)
		return -1;
	return 0;
}

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
  
int main() 
{
	char* msg1 = "hello, world #1"; 
	char* msg2 = "hello, world #2"; 
	char* msg3 = "hello, world #3"; 
    char inbuf[16]; 
    int p[2], i; 
  
    if (pipe(p) < 0) 
        exit(1); 
  
    /* continued */
    /* write pipe */
  
    write(p[1], msg1, 16); 
    write(p[1], msg2, 16); 
    write(p[1], msg3, 16); 
  
    for (i = 0; i < 3; i++) { 
        /* read pipe */
		read(p[0], inbuf, 16); 
        printf("%s\n", inbuf); 
    } 
    return 0; 
} 
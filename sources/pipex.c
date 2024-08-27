#include "pipex.h"

static int errors(char *file)
{
	if(access(file, R_OK) == -1 || access(file, F_OK) == -1)
		return -1;
	return 0;
}

int main(int argc, char **argv)
{
	(void)argc;
	if(errors(argv[1]) == -1)
		return (ft_putstr_fd("Error\n", 2), 0);
    int fd = open("text.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, "Texto original.\n", 16);
	printf("fd %d\n", fd);
    int fd_dup = dup(fd);
    write(fd_dup, "Texto duplicado usando dup().\n", 30);
	printf("fd_dup %d\n", fd_dup);
    int fd_dup2 = dup2(fd, 10);
    write(fd_dup2, "Texto duplicado usando dup2().\n", 31);
	printf("fd_dup2 %d\n", fd_dup2);
    close(fd);
    close(fd_dup);
    close(fd_dup2);

    return 0;
}
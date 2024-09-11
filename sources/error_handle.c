#include "pipex.h"

int print_err(int flag)
{
	if (flag == 1)
		ft_putstr_fd("Error - wrong number of arguments\n", 1);
	else if (flag == 2)
		ft_putstr_fd("Error - failed pipe\n", 1);
	else if (flag == 3)
		ft_putstr_fd("Error - failed to open the file\n", 1);
	return (0);
}

int child_err(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	ft_putstr_fd("Error - failed to initialize the child process\n", 1);
	return (0);
}

int check_arg(int argc, char **argv)
{
	int i;

	i = 0;
	if (access(argv[1], F_OK) != 0)
	{
		ft_putstr_fd("Error - Infile doesn't exist\n", 1);
		exit(0);
	}
	while(i < argc)
	{
		if(ft_strlen(argv[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}
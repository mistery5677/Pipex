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
	else
		ft_printf("Ok\n");
}
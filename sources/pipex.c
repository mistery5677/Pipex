/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:12 by miafonso          #+#    #+#             */
/*   Updated: 2024/08/29 17:52:10 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

static int	print_error(char *error_msg)
{
	ft_putstr_fd (error_msg, 2);
	return (-1);
}

/*Verify if file exists and has read permissions*/
static int	errors(char *file, char *error_msg)
{
	if (access(file, R_OK) == -1 || access (file, F_OK) == -1)
	{
		return (print_error(error_msg));
	}
	return (0);
}

static int	init_child()
{
	int child;
	
	child = fork();
	if(child == -1)
		return -1;
	return 0;
}

int	main (int argc, char **argv)
{
	int fd[2];

	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_RDONLY);
	ft_printf("Parent %d %d\n", fd[0], fd[1]);
	if (errors(argv[1], INFILE_ERROR) == -1
		|| errors(argv[4], OUTFILE_ERROR) == -1 || argc != 5)
		return (-1);
 	if (init_child() == -1)
		return (print_error("Error - Fail to init pipe\n"));
	ft_printf("child %d %d %d\n", fd[0], fd[1], dup2(3, 6));
 	close(fd[0]);
	close(fd[1]);
	return (0);
}

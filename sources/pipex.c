/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:12 by miafonso          #+#    #+#             */
/*   Updated: 2024/08/29 23:24:30 by mistery576       ###   ########.fr       */
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

static int pipex()
{
	int fd[2];
	int child;

	if (pipe(fd) == -1)
		return (print_error("Error - Pipe not initialized\n"));
	child = fork();    
	if (child == -1)
		return (print_error("Error - Child not initialized\n"));
	if (child == 0)
	{
		char *exe_path = "/bin/ls";
		char *args[] = {"ls", "-l", NULL};
		char *env[] = {NULL};

		execve(exe_path, args, env);
		char *tosend = "hello world\n";
		write(fd[1], tosend, ft_strlen(tosend));
		printf("Information send %s\n", tosend);
		
	}
	wait(NULL);
	return (0);
}

int	main (int argc, char **argv)
{
	if (errors(argv[1], INFILE_ERROR) == -1
		|| errors(argv[4], OUTFILE_ERROR) == -1 || argc != 5)
		return (-1);
	if (pipex() == -1)
		return (-1);
	return (0);
}

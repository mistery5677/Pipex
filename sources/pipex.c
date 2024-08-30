/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:12 by miafonso          #+#    #+#             */
/*   Updated: 2024/08/30 17:07:30 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"  

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

static void *find_path(char *cmd, char *envp)
{
	const char *directories[] = {"/bin", "/usr/bin", "/usr/local/bin", NULL};
	int i;

	i = 0;
	while(directories[i])
	{
		i++;
	}
	
	path = 
	return path;
}

/* static void parent_process(char **argv, char **envp, int *fd)
{
	int outfile;

	outfile = open(argv[4], O_RDONLY, 0777);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute_cmd(argv[3], envp);
} */

static void child_process(char **argv, char **envp, int *fd)
{
	int infile;
	char *path;
	
	infile = open(argv[1], O_RDONLY, 0777);
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	path = find_path(argv[2], envp[2]);
}

static int pipex(char **argv, char **envp)
{
	int fd[2];
	int child;
	
	if (pipe(fd) == -1)
		return (print_error("Error - Pipe not initialized\n"));
	child = fork();    
	if (child == -1)
		return (print_error("Error - Child not initialized\n"));
	if (child == 0)
		child_process(argv, envp, fd);	
	waitpid(child, NULL, 0);
	//parent_process();
	
	return (0);
}

int	main (int argc, char **argv, char **envp)
{
	if (errors(argv[1], INFILE_ERROR) == -1
		|| errors(argv[4], OUTFILE_ERROR) == -1 || argc != 5)
		return (-1);
	if (pipex(argv, envp) == -1)
		return (-1);
	return (0);
}

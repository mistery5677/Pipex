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

static void	print_error(char *error_msg)
{
	ft_putstr_fd (error_msg, 2);
}

/*Verify if file exists and has read permissions*/
static int	errors(char *file, char *error_msg)
{
	if (access(file, R_OK) == -1 || access (file, F_OK) == -1)
	{
		return (print_error(error_msg), -1);
	}
	return (0);
}

static char *get_cmd_path(char **envp)
{
	int i;

	i = 0;
	while(envp[i] != NULL)
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
			return envp[i] + 5;
		i++;
	}
	return NULL;
}

static void *find_path(char *cmd, char **envp)
{
	char *path_envp = get_cmd_path(envp);
	char *path = ft_strdup(path_envp);
	char **dir = ft_split(path, ':');
	int i;

	i = 0;
	while(dir[i] != NULL)
	{
		char *full_path;
		full_path = ft_strjoin_gnl(dir[i], "/");
		full_path = ft_strjoin_gnl(full_path, cmd);
		if (access(full_path, F_OK) == 0)
		{
			free(path);
			i++;
			while(dir[i])
			{
				free(dir[i]);
				i++;
			}
			free(dir);
			return full_path;
		}
		free(full_path);
		i++;
	}
	free(dir);
	free(path);
	return NULL;
}

static void parent_process(char **argv, char **envp, int *fd)
{
	int outfile;
	char *cmd_path;
	char **new_argv;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	cmd_path = find_path(argv[3], envp);
	new_argv = ft_split(argv[3], ' ');
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execve(cmd_path, new_argv, envp);
}

static void child_process(char **argv, char **envp, int *fd)
{
	int infile;
	char *cmd_path;
	char **new_argv;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		return print_error("Error - Failed to open the file\n");
	cmd_path = find_path(argv[2], envp);
	new_argv = ft_split(argv[2], ' ');
	// Redirect the output for the fd[1]
 	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(infile);
	// Execute the command
    execve(cmd_path, new_argv, envp);
}

static void pipex(char **argv, char **envp)
{
	int fd[2];
	pid_t child;
	
	if (pipe(fd) == -1)
		return (print_error("Error - Pipe not initialized\n"));
	child = fork();    
	if (child == -1)
		return (print_error("Error - Child not initialized\n"));
	if (child == 0)
		child_process(argv, envp, fd);	
	wait(0);
	parent_process(argv, envp, fd);
}

int	main (int argc, char **argv, char **envp)
{
 	if (errors(argv[1], INFILE_ERROR) == -1
		|| errors(argv[4], OUTFILE_ERROR) == -1 || argc != 5)
		return (-1); 
	pipex(argv, envp);
	return (0);
}

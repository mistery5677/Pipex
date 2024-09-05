/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:12 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/05 17:06:44 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"  

char	*find_path(char *cmd, char **envp)
{
	char	**dir;
	char	**split_cmd;
	char	*full_path;
	char	*path_envp;

	path_envp = get_cmd_path(envp);
	dir = ft_split(path_envp, ':');
	split_cmd = ft_split(cmd, ' ');
	full_path = NULL;
	full_path = find_path_util(full_path, split_cmd, dir);
	return (full_path);
}

static void	parent_process(char **argv, char **envp, int *fd)
{
	char	**new_argv;
	char	*cmd_path;
	int		outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC , 0777);
	cmd_path = find_path(argv[3], envp);
	new_argv = ft_split(argv[3], ' ');
	if (!cmd_path || !new_argv)
	{
		close(outfile);
		free(cmd_path);
		free_double(new_argv);
		return ;
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(fd[1]);
	close(fd[0]);
	execve(cmd_path, new_argv, envp);
	free_double(new_argv);
	free(cmd_path);
}

static int	child_process(char **argv, char **envp, int *fd)
{
	char	**new_argv;
	char	*cmd_path;
	int		infile;

	infile = open(argv[1], O_RDONLY, 0777);
	cmd_path = find_path(argv[2], envp);
	new_argv = ft_split(argv[2], ' ');
	if (infile == -1 || !cmd_path || !new_argv)
	{
		close(infile);
		free(cmd_path);
		free_double(new_argv);
		return (-1);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(infile);
	execve(cmd_path, new_argv, envp);
	free_double(new_argv);
	free(cmd_path);
	return (0);
}

static void	pipex(char **argv, char **envp, int argc)
{
	int		fd[2];
	int		flag;
	pid_t	child;

	flag = 0;
	if (pipe(fd) == -1)
		return (print_error("Error - Pipe not initialized\n"));
	if (argc != 5 || check_commands(argv, envp, argc) == -1)
		return ;
	child = fork();
	if (child == -1)
		return (print_error("Error - Child not initialized\n"));
	if (child == 0)
		flag = child_process(argv, envp, fd);
	wait(0);
	if (flag == 0)
	{
		parent_process(argv, envp, fd);
		return ;
	}
	print_error("Error - Failed to initialize the child\n");
}

int	main(int argc, char **argv, char **envp)
{
	pipex(argv, envp, argc);
	return (0);
}

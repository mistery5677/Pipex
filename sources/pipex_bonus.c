/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:12 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/02 17:49:36 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"  

static char	*find_path(char *cmd, char **envp)
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

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	cmd_path = find_path(argv[3], envp);
	new_argv = ft_split(argv[3], ' ');
	if (!cmd_path || !new_argv || outfile == -1)
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

	infile = open(argv[1], O_RDONLY);
	cmd_path = find_path(argv[2], envp);
	new_argv = ft_split(argv[2], ' ');
	if (infile == -1 || !cmd_path || !new_argv)
	{
		free(cmd_path);
		free_double(new_argv);
		print_error("Error - Failed to open the file\n");
		return (-1);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(infile);
	free_double(new_argv);
	free(cmd_path);
	free_all(new_argv, cmd_path);
	return (0);
}

static void	pipex(char **argv, char **envp)
{
	int		fd[2];
	int		flag;
	pid_t	child;

	flag = 0;
	if (pipe(fd) == -1)
		return (print_error("Error - Pipe not initialized\n"));
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
	print_error("Error - Failed ");
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		print_error("Error - Invalid number of args\n");
		return (-1);
	}
	if (check_commands(argv, envp, argc) == -1)
		return (-1);
	pipex(argv, envp);
	return (0);
}
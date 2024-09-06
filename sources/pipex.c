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

static void execute(char *argv, char **envp)
{
	char *cmd_path;
	char **new_argv;

	cmd_path = find_path(argv, envp);
	new_argv = ft_split(argv, ' ');
	execve(cmd_path, new_argv, envp);
	free_double(new_argv);
	free(cmd_path);
}

static int child_process(char **argv, char **envp, int *fd)
{
	pid_t	child;
	int		infile;

	child = fork();
	if (child == 0)
	{
		infile = open(argv[1], O_RDONLY, 0777);
		if (infile == -1)
			return -1;
		dup2(fd[1], STDOUT_FILENO);
		dup2(infile, STDIN_FILENO);
		execute(argv[2], envp);
		close(fd[0]);
		close(infile);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		waitpid(child, NULL, 0);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int outfile;
	int fd[2];

	if (argc != 5 || check_commands(argv, envp) == -1)
		return 0;
	if (pipe(fd) == -1)
		return -1;
	if (child_process(argv, envp, fd) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (0);
	}
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		return (0);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute(argv[3], envp);
	close(outfile);
}

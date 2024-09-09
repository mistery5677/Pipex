/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:12 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/09 18:11:12 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process(char *argv, char **envp)
{
	pid_t	child;
	int		fd[2];

	if (pipe(fd) == -1)
		return ;
	child = fork();
	if (child == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(child, NULL, 0);
	}
}

static void here_doc_util(char *limitter, int *fd)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strcmp(limitter, line) == 0)
		{
			free(line);
			close(fd[1]);
			close(fd[0]);
			exit(0);
		}
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
		line = get_next_line(0);
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}
static void	here_doc(char **argv)
{
	int		fd[2];
	pid_t	child;

	if (pipe(fd) == -1)
		return ;
	child = fork();
	if (child == 0)
		here_doc_util(argv[2], fd);
	else
	{
		dup2(fd[0], STDIN_FILENO);
		wait(0);
		close(fd[1]);
		close(fd[0]);
	}
}

static int	open_file(char *file, int flag)
{
	int	fd;

	fd = 0;
	if (flag == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return (fd);
	}
	else if (flag == 2)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (fd);
	}
	else
	{
		fd = open(file, O_RDONLY, 0777);
		return (fd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	int	i;

	i = 2;
	infile = -1;
	outfile = -1;
	if (argc < 5)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		i = 3;
		outfile = open_file(argv[argc - 1], 1);
		dup2(outfile, STDOUT_FILENO);
		here_doc(argv);
	}
	else
	{
		infile = open_file(argv[1], 3);
		outfile = open_file(argv[argc - 1], 2);
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
	}
	while (i < argc - 2)
		child_process(argv[i++], envp);
	execute(argv[argc - 2], envp);
	if (outfile != -1)
		close(outfile);
	if (infile != -1)
		close(infile);
}
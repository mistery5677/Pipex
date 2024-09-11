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

static void	here_doc_util(char *limitter, int *fd, int outfile)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line && ft_strcmp(limitter, line) != 0)
	{
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
		line = get_next_line(0);
	}
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	exit(0);
}

static void	here_doc(int argc, char **argv, int outfile)
{
	int		fd[2];
	pid_t	child;

	if (argc != 6)
	{
		ft_putstr_fd("Error - Wrong number of arguments\n", 1);
		close(outfile);
		exit(0);
	}
	if (pipe(fd) == -1)
		return ;
	child = fork();
	if (child == 0)
		here_doc_util(argv[2], fd, outfile);
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
		dup2(fd, STDOUT_FILENO);
	}
	else if (flag == 2)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else
	{
		fd = open(file, O_RDONLY, 0644);
		dup2(fd, STDIN_FILENO);
	}
	return (fd);
}

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	int	i;

	i = 2;
	infile = 0;
	if (argc < 5)
		return print_err(1);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		i = 3;
		outfile = open_file(argv[argc - 1], 1);
		here_doc(argc, argv, outfile);
		close(outfile);
	}
	else
	{
		check_arg(argc, argv);
		infile = open_file(argv[1], 3);
		outfile = open_file(argv[argc - 1], 2);
	}
	while (i < argc - 2)
		child_process(argv[i++], envp);
	execute(argv[argc - 2], envp);
	close(outfile);
	close(infile);
}

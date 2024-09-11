/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:12 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/06 15:32:44 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	child_process(char **argv, char **envp, int *fd)
{
	pid_t	child;
	int		infile;

	child = fork();
	if (child == -1)
		return (-1);
	if (child == 0)
	{
		infile = open(argv[1], O_RDONLY, 0644);
		if (infile == -1)
			return (-1);
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
	int	outfile;
	int	fd[2];

	if (argc != 5 || check_arg(argc, argv) == -1)
		return print_err(1);
	if (pipe(fd) == -1)
		return print_err(2);
	if (child_process(argv, envp, fd) == -1)
		return child_err(fd);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		return print_err(3);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute(argv[3], envp);
	close(outfile);
}

/*
OLD_PATH=$PATH
unset PATH
PATH=$OLD_PATH
env -i ./pipex etc*/
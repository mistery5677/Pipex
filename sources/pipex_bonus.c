/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:12 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/06 16:33:30 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"  

static void	child_process(char *argv, char **envp)
{
	pid_t	child;
	int		fd[2];

	if(pipe(fd) == -1)
		return ;
	child = fork();
	if(child == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(child, NULL, 0);
	}
}

static void here_doc(char **argv)
{
	char *line;
	pid_t	child;
	
	child = fork();
	if (child == 0)
	{
		line = get_next_line(0);
		while(line)
		{
			if (ft_strncmp(line, argv[2], ft_strlen(line) - 1) == 0)
			{
				free(line);
				exit(0);
			}
			free(line);
			line = get_next_line(0);
		}
	}
	wait(0);
}

static int open_file(char *file, int flag)
{
	int fd;

	fd = 0;
	if (flag == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return fd;
	}
	else if (flag == 2)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return fd;
	}
	else
	{
		fd = open(file, O_RDONLY);
		return fd;
	}
}

int main(int argc, char **argv, char **envp)
{
	int infile;
	int outfile;
	int i;
	
	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		outfile = open_file(argv[argc - 1], 1);
		here_doc(argv);
	}
	else
	{
		infile = open_file(argv[1], 3);
		outfile = open_file(argv[argc - 1], 2);
		dup2(infile, STDIN_FILENO);
	}
	while(i < argc - 2)
		child_process(argv[i++], envp);
	dup2(outfile, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
}
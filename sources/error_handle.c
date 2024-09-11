/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:50:46 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/11 14:57:04 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	print_err(int flag)
{
	if (flag == 1)
		ft_putstr_fd("Error - wrong number of arguments\n", 2);
	else if (flag == 2)
		ft_putstr_fd("Error - failed pipe\n", 2);
	else if (flag == 3)
		ft_putstr_fd("Error - failed to open the file\n", 2);
	else if (flag == 4)
		ft_putstr_fd("Error - No command found", 2);
	return (0);
}

int	child_err(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	ft_putstr_fd("Error - failed to initialize the child process\n", 2);
	return (0);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	if (access(argv[1], F_OK) != 0)
	{
		ft_putstr_fd("Error - Infile doesn't exist\n", 2);
		exit(0);
	}
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

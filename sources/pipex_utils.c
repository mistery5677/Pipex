/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:44:34 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/02 16:52:15 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	print_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
}

char	*get_cmd_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_path_util(char *full_path, char **split_cmd, char **dir)
{
	int	i;

	i = 0;
	while (dir[i] != NULL)
	{
		full_path = ft_strjoin(dir[i], "/");
		full_path = ft_strjoin_gnl(full_path, split_cmd[0]);
		if (access(full_path, F_OK) == 0)
		{
			free_double(dir);
			free_double(split_cmd);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

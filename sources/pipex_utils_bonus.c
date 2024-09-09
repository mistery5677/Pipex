/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:44:34 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/09 17:27:57 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static char	*find_path_util(char *full_path, char **split_cmd, char **dir)
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
	free_double(dir);
	free_double(split_cmd);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**dir;
	char	**split_cmd;
	char	*full_path;
	char	*path_envp;

	path_envp = get_cmd_path(envp);
	if (path_envp == NULL)
		exit(0);
	dir = ft_split(path_envp, ':');
	split_cmd = ft_split(cmd, ' ');
	full_path = NULL;
	full_path = find_path_util(full_path, split_cmd, dir);
	return (full_path);
}

void	execute(char *argv, char **envp)
{
	char	*cmd_path;
	char	**new_argv;

	cmd_path = find_path(argv, envp);
	new_argv = ft_split(argv, ' ');
	if (cmd_path == NULL || new_argv == NULL)
	{
		free_double(new_argv);
		free(cmd_path);
		return ;
	}
	//execve(cmd_path, new_argv, envp);
	free_double(new_argv);
	free(cmd_path);
}

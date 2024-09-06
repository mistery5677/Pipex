/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:31 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/02 16:38:32 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libraries/libft/libft.h"
# include <sys/wait.h>
# define INFILE_ERROR "Error - Infile invalid permissions"
# define OUTFILE_ERROR "Error - Outfile invalid permissions"

char	*find_path(char *cmd, char **envp);
char	*find_path_util(char *full_path, char **split_cmd, char **dir);
char	*get_cmd_path(char **envp);
void	print_error(char *error_msg);
void	free_double(char **str);
int     check_commands(char **argv, char **envp);

#endif
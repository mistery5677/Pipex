/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:22:04 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/06 16:22:05 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libraries/libft/libft.h"
# include <sys/wait.h>

char	*find_path(char *cmd, char **envp);
char	*get_cmd_path(char **envp);
void	free_double(char **str);
void	execute(char *argv, char **envp);
int     print_err(int flag);
int     child_err(int *fd);
int     check_arg(int argc, char **argv);

#endif
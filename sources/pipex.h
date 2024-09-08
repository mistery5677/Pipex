/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:31 by miafonso          #+#    #+#             */
/*   Updated: 2024/09/06 15:16:22 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
#include "../libraries/libft/libft.h"
#include <sys/wait.h>

char *find_path(char *cmd, char **envp);
char *get_cmd_path(char **envp);
void free_double(char **str);
void execute(char *argv, char **envp);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:27:39 by ihibti            #+#    #+#             */
/*   Updated: 2024/04/29 15:10:34 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "sys/types.h"
# include <fcntl.h>
# include <unistd.h>
# include <wait.h>

void	child_1(int fd[2], char **env, char **av);
void	child(int fd[2], char **env, char **av);
char	**fetch_cmd(char *av);
void	do_cmd(char **cmd, char **env);
char	*pathfinder(char *cmd, char **path_t);
void	disp_error(char *msg, char **arg1, char **arg2);

#endif

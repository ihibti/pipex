/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:27:32 by ihibti            #+#    #+#             */
/*   Updated: 2024/04/29 14:40:22 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_cmd(char **cmd, char **env)
{
	char	*path;
	char	**temp_path;
	int		i;

	i = 0;
	if (access(cmd[0], F_OK) == 0)
		path = cmd[0];
	else
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], "PATH", 4) == 0)
				break ;
			i++;
		}
		if (env[i] == NULL)
			disp_error("path not found 5\n", cmd, NULL);
		temp_path = ft_split(env[i], ':');
		path = pathfinder(cmd[0], temp_path);
		if (!path)
			disp_error("command not found 1", cmd, temp_path);
	}
	execve(path, cmd, env);
	disp_error("command not found\n", NULL, cmd);
	exit(1);
}

char	**fetch_cmd(char *av)
{
	char	**ret;

	ret = ft_split(av, ' ');
	if (!ret)
		exit(1);
	return (ret);
}

char	*pathfinder(char *cmd, char **path_t)
{
	int		i;
	char	*cmd_temp;
	char	*add_slash;

	if (!path_t)
		return (NULL);
	i = 0;
	add_slash = ft_strjoin("/", cmd);
	if (!add_slash)
		return (0);
	while (path_t[i])
	{
		cmd_temp = ft_strjoin(path_t[i], add_slash);
		if (!cmd_temp)
			return (free(add_slash), NULL);
		if (access(cmd_temp, F_OK) == 0)
			return (free(add_slash), cmd_temp);
		free(cmd_temp);
		i++;
	}
	free(add_slash);
	return (NULL);
}

void	disp_error(char *msg, char **arg1, char **arg2)
{
	if (arg1)
		free_error(arg1);
	if (arg2)
		free_error(arg2);
	ft_putstr_fd(msg, 2);
	exit(1);
}

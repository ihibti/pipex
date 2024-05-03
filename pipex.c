/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:24:39 by ihibti            #+#    #+#             */
/*   Updated: 2024/04/29 15:22:01 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	id[2];

	if (ac != 5)
		return (printf("nombre d'arguments incorrect\n"), 1);
	if (pipe(fd) == -1)
		return (1);
	id[0] = fork();
	if (id[0] == -1)
		return (close(fd[0]), close(fd[1]), 1);
	if (id[0] == 0)
		child(fd, env, av);
	id[1] = fork();
	if (id[1] == -1)
		return (close(fd[0]), close(fd[1]), 1);
	if (id[1] == 0)
		child_1(fd, env, av);
	close(fd[0]);
	close(fd[1]);
	waitpid(id[0], 0, 0);
	waitpid(id[1], 0, 0);
	return (0);
}

void	child(int fd[2], char **env, char **av)
{
	int	fd_first;

	close(fd[0]);
	fd_first = open(av[1], O_RDONLY);
	if (fd_first == -1)
	{
		perror(av[1]);
		close(fd[1]);
		exit(1);
	}
	if (dup2(fd_first, STDIN_FILENO) == -1)
	{
		close(fd_first);
		exit(EXIT_FAILURE);
	}
	close(fd_first);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	do_cmd(fetch_cmd(av[2]), env);
}

void	child_1(int fd[2], char **env, char **av)
{
	int	fd_sec;

	close(fd[1]);
	fd_sec = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_sec == -1)
	{
		perror(av[4]);
		close(fd[0]);
		exit(1);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	if (dup2(fd_sec, STDOUT_FILENO) == -1)
	{
		close(fd_sec);
		exit(EXIT_FAILURE);
	}
	close(fd_sec);
	do_cmd(fetch_cmd(av[3]), env);
}

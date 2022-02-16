/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:35:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/16 18:01:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "ps_tester.h"

int	get_rnd_nbr(t_data *data, const char *a, const char *b)
{
	pid_t	pid;
	int		fd[2];
	char	*line;
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		return (perror_n_ret("pipe"));
	if ((pid = fork()) == -1)
		return (perror_n_ret("fork"));
	else if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror_n_ret("dup2"));
		close_fds(fd);
		execl(RND_PATH, RND_PATH, a, b, (char *) NULL);
		return (perror_n_ret("execl"));
	}
	else
	{
		close(fd[1]);
		line = get_next_line(fd[0]);
		data->rnd = ft_split(line, ' ');
		if (data->rnd == NULL)
			status = -1;
		free(line);
		close(fd[0]);
	}
	return (status);
}

int	launch_checker(t_data *data)
{
	pid_t	pid;
	pid_t	pid2;
	int		fd[2];
	int		fd2[2];

	if (pipe(fd) == -1)
		return (perror_n_ret("pipe"));
	if ((pid = fork()) == -1)
		return (perror_n_ret("fork"));
	else if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror_n_ret("dup2")); 
		close_fds(fd);

		if (pipe(fd2) == -1)
			return (perror_n_ret("pipe"));
		if ((pid2 = fork()) == -1)
			return (perror_n_ret("fork"));
		else if (pid2 == 0)
		{
			if (dup2(fd2[0], STDIN_FILENO) == -1)
				return (perror_n_ret("dup2")); 
			close_fds(fd2);
			execv(CHK_PATH, data->rnd);
			return (perror_n_ret("execv"));
		}
		else
		{
			if (dup2(fd2[1], STDOUT_FILENO) == -1)
				return (perror_n_ret("dup2")); 
			close_fds(fd2);
			execv(PS_PATH, data->rnd);
			return (perror_n_ret("execv"));
		}
	}
	else
	{
		close(fd[1]);
		char *line = get_next_line(fd[0]);
		if (ft_strcmp(line, "OK\n") == 0)
			data->status = 0;
		else
			data->status = 1;
		free(line);
		close(fd[0]);
	}
	return (0);
}

int	get_nbr_inst(t_data *data)
{
	pid_t	pid;
	pid_t	pid2;
	int		fd[2];
	int		fd2[2];

	if (pipe(fd) == -1)
		return (perror_n_ret("pipe"));
	if ((pid = fork()) == -1)
		return (perror_n_ret("fork"));
	else if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror_n_ret("dup2"));
		close_fds(fd);
		if (pipe(fd2) == -1)
			return (perror_n_ret("pipe"));
		if ((pid2 = fork()) == -1)
			return (perror_n_ret("fork"));
		else if (pid2 == 0)
		{
			if (dup2(fd2[0], STDIN_FILENO) == -1)
				return (perror_n_ret("dup2"));
			close_fds(fd2);
			execl(WC_PATH, "wc", "-l", NULL);
			return (perror_n_ret("execl"));
		}
		else
		{
			if (dup2(fd2[1], STDOUT_FILENO) == -1)
				return (perror_n_ret("dup2"));
			close_fds(fd2);
			execv(PS_PATH, data->rnd);
			return (perror_n_ret("execv"));
		}
	}
	else
	{
		close(fd[1]);
		char *line = get_next_line(fd[0]);
		data->nbr_inst = (unsigned int) ft_atoi(line);
		free(line);
		close(fd[0]);
	}
	return (0);
}

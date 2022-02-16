/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:35:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/16 01:52:08 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include "test.h"

int	get_random_number(t_data *data, const char *a, const char *b)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
		close(fd[0]);
		if (execl(RND_PATH, RND_PATH, a, b, (char *) NULL) == -1)
		{
			perror("execl");
			close(fd[1]);
			return (-1);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		line = get_next_line(fd[0]);
		data->rnd = ft_split(line, ' ');
		free(line);
		close(fd[0]);
	}
}

int	do_test(t_data *data)
{
	pid_t	pid;
	pid_t	pid2;
	int		fd[2];
	int		fd2[2];
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		pipe(fd2);
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(fd2[0], STDIN_FILENO);
			close(fd2[0]);
			close(fd2[1]);
			execv(CHK_PATH, data->rnd);
		}
		else
		{
			dup2(fd2[1], STDOUT_FILENO);
			close(fd2[0]);
			close(fd2[1]);
			execv(PS_PATH, data->rnd);
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
}

int	make_test(const char *a, const char *b)
{
	t_data	data;

	get_random_number(&data, a, b);
	do_test(&data);
	if (data.status == 0)
		ft_printf(STR_OK);
	else
		ft_printf(STR_KO);
}

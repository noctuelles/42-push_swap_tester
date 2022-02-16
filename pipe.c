/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:35:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/16 13:19:20 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include "test.h"
#include <limits.h>

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

int	do_checker(t_data *data)
{
	pid_t	pid;
	pid_t	pid2;
	int		fd[2];
	int		fd2[2];
	int		ret;

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

int	get_nbr_inst(t_data *data)
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
			execl("/usr/bin/wc", "wc", "-l", NULL);
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
		data->nbr_inst = (size_t) ft_atoi(line);
		free(line);
		close(fd[0]);
	}
}

void	free_tab(char **tab)
{
	t_index	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	sample_test(unsigned int nbr, const char *a, const char *b)
{
	t_index			i;
	t_sample		sample;
	t_data			data;

	ft_memset(&sample, 0, sizeof(sample));
	sample.smallest = UINT_MAX;
	sample.biggest = 0;
	i = 0;
	while (i < nbr)
	{
		get_random_number(&sample.data, a, b);
		get_nbr_inst(&sample.data);
		do_checker(&sample.data);
		if (sample.data.nbr_inst < sample.smallest)
			sample.smallest = sample.data.nbr_inst;
		if (sample.data.nbr_inst > sample.biggest)
			sample.biggest = sample.data.nbr_inst;
		sample.average += sample.data.nbr_inst;
		sample.status += sample.data.status;
		i++;
	}
	sample.average /= nbr;
	//free_tab(data.rnd);
	if (sample.status == 0)
		ft_printf(STR_SAMPLE_OK, sample.smallest, sample.average,
				sample.biggest);
	else
		ft_printf(STR_SAMPLE_KO);
}

int	make_test(const char *a, const char *b)
{
	t_data	data;

	get_random_number(&data, a, b);
	get_nbr_inst(&data);
	do_checker(&data);
	free_tab(data.rnd);
	if (data.status == 0)
		ft_printf(STR_TEST_OK, data.nbr_inst);
	else
		ft_printf(STR_KO);
}

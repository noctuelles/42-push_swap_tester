/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:35:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/15 18:30:40 by plouvel          ###   ########.fr       */
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

static char	**make_tab_from_list(t_list *list)
{
	char	**tab;
	size_t	lst_size;
	t_index	i;

	lst_size = ft_lstsize(list);
	tab = (char **) malloc((lst_size + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < lst_size)
	{
		tab[i] = (char *) list->content;
		list = list->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	get_ps_inst(t_data *data)
{
	pid_t	pid;
	int		fd[2];
	char	*line;
	t_list	*elem;

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
		if (execv(PS_PATH, data->rnd) == -1)
		{
			perror("execv");
			close(fd[1]);
			return (-1);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		while ((line = get_next_line(fd[0])))
		{
			elem = ft_lstnew(line);
			if (!elem)
				return (-1);
			ft_lstadd_back(&data->inst_list, elem);
			data->inst_nbr++;
		}
		data->inst = make_tab_from_list(data->inst_list);
		close(fd[0]);
	}
}

int	check_inst(t_data *data)
{
	pid_t	pid;
	int		fd[2];
	char	*line;
	t_list	*elem;

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
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
		close(fd[0]);
		close(fd[1]);
		if (execv(CHK_PATH, data->rnd) == -1)
		{
			perror("execv");
			close(fd[1]);
			return (-1);
		}
	}
	else
	{
		close(fd[0]);
		for (int i = 0; data->inst[i]; i++)
			ft_putstr_fd(data->inst[i], fd[1]);
		close(fd[1]);
		waitpid(pid, &data->chk_status, 0);
		if (WIFEXITED(data->chk_status))
			data->chk_status = WEXITSTATUS(data->chk_status);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:26:25 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/16 18:01:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ps_tester.h"
#include <stdio.h>
#include "ft_printf.h"

void	close_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	free_tab(char **tab)
{
	t_index	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (-1);
}

int	perror_n_ret(const char *str)
{
	perror(str);
	return (-1);
}

int	throw_error(void)
{
	ft_printf(STR_INTERNAL_ERR);
	return (1);
}

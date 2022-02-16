/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:23:10 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/16 18:00:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_tester.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <limits.h>

int	sample_test(unsigned int nbr, const char *a, const char *b)
{
	t_index			i;
	t_sample		sample;

	ft_memset(&sample, 0, sizeof(sample));
	sample.smallest = UINT_MAX;
	sample.biggest = 0;
	i = 0;
	while (i < nbr)
	{
		if (get_rnd_nbr(&sample.data, a, b) == -1)
			return (-1);
		if (get_nbr_inst(&sample.data) == -1)
			return (free_tab(sample.data.rnd));
		if (launch_checker(&sample.data) == -1)
			return (free_tab(sample.data.rnd));

		if (sample.data.nbr_inst < sample.smallest)
			sample.smallest = sample.data.nbr_inst;
		if (sample.data.nbr_inst > sample.biggest)
			sample.biggest = sample.data.nbr_inst;
		sample.average += sample.data.nbr_inst;
		sample.status += sample.data.status;

		(void) free_tab(sample.data.rnd);
		i++;
	}
	sample.average /= nbr;
	if (sample.status == 0)
		ft_printf(STR_SAMPLE_OK, sample.smallest, sample.average,
				sample.biggest);
	else
		ft_printf(STR_SAMPLE_KO);
	return (0);
}

int	make_test(const char *a, const char *b)
{
	t_data	data;

	if (get_rnd_nbr(&data, a, b) == -1)
		return (-1);
	if (get_nbr_inst(&data) == -1)
		return (free_tab(data.rnd));
	if (launch_checker(&data) == -1)
		return (free_tab(data.rnd));

	free_tab(data.rnd);
	if (data.status == 0)
		ft_printf(STR_TEST_OK, data.nbr_inst);
	else
		ft_printf(STR_KO);
	return (0);
}

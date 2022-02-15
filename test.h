/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:46:29 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/15 18:30:41 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "libft.h"

# define RND_PATH "random.sh"
# define PS_PATH "push_swap"
# define CHK_PATH "checker"

typedef struct s_data
{
	char	**rnd;
	char	**inst;
	t_list	*inst_list;
	size_t	inst_nbr;
	int		chk_status;
}				t_data;

int	check_inst(t_data *data);
int	get_ps_inst(t_data *data);
int	get_random_number(t_data *data, const char *a, const char *b);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:46:29 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/16 01:49:44 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "libft.h"

# define RND_PATH "random.sh"
# define PS_PATH "push_swap"
# define CHK_PATH "checker"

# define HEADER "\
{36;1}/* ************************************************************************** */\n\
{36;1}/*                                                                            */\n\
{36;1}/*                                                        {96;1}:::      ::::::::{0}   {36;1}*/\n\
{36;1}/*   {36;1}Push_Swap_Benchmark{0}                                {96;1}:+:      :+:    :+:{0}   {36;1}*/\n\
{36;1}/*                                                    {96;1}+:+ +:+         +:+{0}     {36;1}*/\n\
{36;1}/*   {36;3}By: {1}plouvel{36;3} {4}<plouvel@student.42.fr>{0}            {96;1}+#+  +:+       +#+{0}        {36;1}*/\n\
{36;1}/*                                                {96;1}+#+#+#+#+#+   +#+{0}           {36;1}*/\n\
{36;1}/*                                                     {96;1}#+#    #+#{0}             {36;1}*/\n\
{36;1}/*                                                    {96;1}###   ########.fr{0}       {36;1}*/\n\
{36;1}/*                                                                            */\n\
{36;1}/* ************************************************************************** */{0}\n\n"

# define STR_WARNING_TITLE "Warning"
# define STR_INIT          "Checking test condition"
# define STR_BASIC_TEST    "Performing simple check"
# define STR_SAMPLE_TEST   "Sampling your push_swap"

# define STR_WARNING "\
This Benchmark {1}doesn't{0} replace human check :\n\n\
	- It doesn't look for leaks.\n\
	- It doesn't try to break your program.\n\n\
Make sure you do a {1}lot of tests{0} on your part !\n\n"

# define STR_CHECK_PS	"{1;3}Checking if a push_swap program is available and executable :{0} "
# define STR_CHECK_RND	"{1;3}Checking if a randomizer is available and executable :{0} "
# define STR_CHECK_CHK	"{1;3}Checking if a checker is available and executable :{0} "
# define STR_CHECK_KO   "{31;1}Cannot continue test.{0}\n\n"
# define STR_CHECK_OK   "{32;1}Test can be run.{0}\n\n"
# define STR_OK         "{32;1}OK{0}\n\n"
# define STR_KO         "{31;1}KO{0}\n\n"
# define STR_TEST_1     "{1;3}Sorting a basic list (5 numbers)...{0} "
# define STR_TEST_2     "{1;3}Sorting a basic list (100 numbers)...{0} "
# define STR_TEST_3     "{1;3}Sorting a basic list (500 numbers)...{0} "

# define STR_SAMPLE_1   "{1;3}Performing %u test with a range between [%s;%s]...{0}\n\n"
# define NBR_TEST_1 50

# define OK 2
# define KO 1

typedef struct s_data
{
	char	**rnd;
	int		status;
}				t_data;

typedef struct s_sample
{
}				t_sample;

int	check_inst(t_data *data);
int	get_ps_inst(t_data *data);
int	get_random_number(t_data *data, const char *a, const char *b);

#endif

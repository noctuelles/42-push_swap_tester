/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_tester.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:46:29 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/16 18:01:05 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_TESTER_H
# define PS_TESTER_H

# include "libft.h"
# include "user_define.h"

# define HEADER "\
\n{36;1}/* ************************************************************************** */\n\
{36;1}/*                                                                            */\n\
{36;1}/*                                                        {96;1}:::      ::::::::{0}   {36;1}*/\n\
{36;1}/*   {36;1;4}Push_Swap_Benchmark{0}                                {96;1}:+:      :+:    :+:{0}   {36;1}*/\n\
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
# define STR_DONE_TEST     "Thanks for using the tester. Goodbye !"

# define STR_WARNING "\
This Benchmark {1}doesn't{0} replace human check :\n\n\
\t- It doesn't look for leaks.\n\
\t- It doesn't try to break your program by inputing wrong values.\n\
\t- It doesn't test the checker provided.\n\n\
Make sure you do a {1}lot of tests{0} on your part !\n\n"

# define STR_CHECK_PS	"{1;3}Checking if a push_swap program is available and executable :{0} "
# define STR_CHECK_RND	"{1;3}Checking if a randomizer is available and executable :{0} "
# define STR_CHECK_CHK	"{1;3}Checking if a checker is available and executable :{0} "
# define STR_CHECK_KO   "{31;1}Cannot continue test.{0}\n\n"
# define STR_CHECK_OK   "{32;1}Test can be run.{0}\n\n"
# define STR_OK         "{32;1}OK{0}\n\n"
# define STR_TEST_OK    "{32;1}OK{0} in {1}%u{0} instruction(s).\n\n"
# define STR_KO         "{31;1}KO{0}\n\n"
# define STR_TEST_1     "{1;3}Sorting a basic list (5 numbers)...{0} "
# define STR_TEST_2     "{1;3}Sorting a basic list (100 numbers)...{0} "
# define STR_TEST_3     "{1;3}Sorting a basic list (500 numbers)...{0} "

# define STR_SAMPLE_1   "{1;3}Performing %u test with a range between [%s;%s]...{0}\n\n"

# define STR_SAMPLE_OK	"\t*  {1;32}OK{0} ! {4}You can find the details bellow :{0}\n\t|\n\
\t|-\t{1}Smallest{0} number of instruction used :  {32;1}%u{0}\n\t|\n\
\t|-\t{1}Average{0}  number of instruction used :  {94;1}%u{0}\n\t|\n\
\t|-\t{1}Maximum{0}  number of instruction used :  {31;1}%u{0}\n\n"

# define STR_SAMPLE_KO	"\t*  {31;1}KO{0} ! {4}One of the test failed the checker :{0}\n\t|\n\
\t|-\tYou can find the random number tested in the file {1}failed_test.log{0}.\n\n"

# define STR_INTERNAL_ERR  "{1;31}Internal error.{0}\n"

# define OK 2
# define KO 1

typedef struct s_data
{
	char			**rnd;
	unsigned int	nbr_inst;
	int				status;
}				t_data;

typedef struct s_sample
{
	t_data			data;
	unsigned int	smallest;
	unsigned int	biggest;
	unsigned int	average;
	int				status;
}				t_sample;

/* pipe.c */

int		get_rnd_nbr(t_data *data, const char *a, const char *b);
int		get_nbr_inst(t_data *data);
int		launch_checker(t_data *data);

/* test.c */

int		make_test(const char *a, const char *b);
int		sample_test(unsigned int nbr, const char *a, const char *b);

/* utils.c */

void	close_fds(int fd[2]);
int		free_tab(char **tab);
int		perror_n_ret(const char *str);
int		throw_error(void);

#endif

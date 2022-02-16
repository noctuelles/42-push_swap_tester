#include <unistd.h>
#include <stdio.h>
#include "ft_printf.h"
#include "test.h"

void	print_center_banner(const char *style, const char *str)
{
	unsigned int	nbr_wildcard;
	size_t			str_len;
	t_index			i;

	i = 0;
	str_len = ft_strlen(str);
	nbr_wildcard = 74 - str_len;
	ft_putstr("/* ");
	while (i++ < (nbr_wildcard / 2) - 1)
		ft_putchar('*');
	ft_putchar(' ');
	ft_printf(style);
	ft_printf(str);
	ft_printf("{0}");
	ft_putchar(' ');
	while (i++ < nbr_wildcard - 1)
		ft_putchar('*');
	ft_putstr(" */\n\n");
}

int	check_files(void)
{
	int	ret;

	ret = OK;
	ft_printf(STR_CHECK_PS);
	if (access(PS_PATH, F_OK | X_OK) == -1)
	{
		ft_printf(STR_KO);
		ret = KO;
	}
	else
		ft_printf(STR_OK);
	ft_printf(STR_CHECK_RND);
	if (access(RND_PATH, F_OK | X_OK) == -1)
	{
		ret = KO;
		ft_printf(STR_KO);
	}
	else
		ft_printf(STR_OK);
	ft_printf(STR_CHECK_CHK);
	if (access(CHK_PATH, F_OK | X_OK) == -1)
	{
		ret = KO;
		ft_printf(STR_KO);
	}
	else
		ft_printf(STR_OK);
	return (ret);
}

int main()
{
	t_data	data = {0};

	ft_printf(HEADER);
	print_center_banner("{1;4}", STR_WARNING_TITLE);
	ft_printf(STR_WARNING);
	print_center_banner("{1;4}", STR_INIT);
	if (check_files() == KO)
	{
		ft_printf(STR_CHECK_KO);
		return (KO);
	}
	else
		ft_printf(STR_CHECK_OK);
	print_center_banner("{1;4}", STR_BASIC_TEST);
	ft_printf(STR_TEST_1);
	make_test("0", "9");
	ft_printf(STR_TEST_2);
	make_test("0", "49");
	ft_printf(STR_TEST_3);
	make_test("0", "500");
}

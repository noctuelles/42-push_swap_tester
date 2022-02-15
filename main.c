#include <unistd.h>
#include <stdio.h>
#include "test.h"

int main()
{
	t_data	data = {0};

	get_random_number(&data, "0", "4");
	get_ps_inst(&data);
	check_inst(&data);
}

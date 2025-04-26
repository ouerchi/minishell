#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int	ft_env(env_lst)
{
	int	i;
	char *my_env;

	if (!env || !*env)
		return (0);
	i = 0;
	while(env[i])
	{
		my_env = ft_strchr((const char *)env[i], '=');
		if (!my_env)
		{
			i++;
			continue;
		}
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
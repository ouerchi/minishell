/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:34:50 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/11 20:51:51 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_no_args(char **args, char **env)
{
	int	i;

	if (!args || !env)
		return (1);
	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}		
	return (0);
}

void	export_args(t_config *config, char *arg)
{
	char	*tmp;

	tmp = arg;
	
}

int	ft_export(t_config *config, char **args)
{
	char	**env;
	int		i;

	env = config->env;
	if (!args[1])
		return (if_no_args(args, env));
	i = 1;
	while (args[i])
	{
		export_args(config, ft_strdup(args[i]));
		i++;
	}
	return (0);
}

/*

equal_pos = srch for '='

name =  

value = equal_pos + 1;


*/
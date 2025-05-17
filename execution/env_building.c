/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:47 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/16 15:17:19 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_env(t_config *config)
{
	char	*tmp;
	int		shell_level;

	if (!ft_getenv(config->env, "PATH"))
		ft_setenv(config, "PATH", \
			ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	if (!ft_getenv(config->env, "SHLVL"))
		ft_setenv(config, "SHLVL", ft_strdup("1"));
	else
	{
		tmp = ft_getenv(config->env, "SHLVL");
		shell_level = ft_atoi(tmp) + 1;
		tmp = ft_itoa(shell_level);
		ft_setenv(config, "SHLVL", tmp);
	}
	if (!ft_getenv(config->env, "_"))
		ft_setenv(config, "_", ft_strdup("/usr/bin/env"));
	if (!ft_getenv(config->env, "PWD"))
	{
		tmp = NULL;
		tmp = getcwd(tmp, 0);
		ft_setenv(config, "PWD", ft_strdup(tmp));
	}
	update_env_array(config);
}

void	init_env(t_config *config, char **env)
{
	// config->env = env;
	config->env = get_env(env);
	config->env_lst = NULL;
	config->env_lst = get_env_lst(config);
	check_env(config);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_building_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:22:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/15 19:59:20 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_env_lst(t_config *config)
{
	char	**env;
	int		i;
	t_env	*lst;

	if (config->env_lst)
		return (free_env_lst(config->env_lst), NULL);
	env = config->env;
	if (!env)
		return (NULL);
	lst = NULL;
	i = 0;
	while (env[i])
	{
		append_env_lst(&lst, env[i]);
		if (!lst)
			return (NULL);
		i++;
	}
	return (lst);
}

int	fail_check(char ***env, int i)
{
	int	j;

	if (!(*env)[i])
	{
		j = 0;
		while (j < i)
			free((*env)[j++]);
		free(*env);
		return (0);
	}
	return (1);
}

char	**get_env(char **real_env)
{
	char	**env;
	int		i;
	int		count;

	if (!real_env || !(*real_env))
		return (NULL);
	count = 0;
	while (real_env[count])
		count++;
	env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		env[i] = ft_strdup(real_env[i]);
		if (!fail_check(&env, i))
			return (NULL);
		i++;
	}
	env[count] = NULL;
	return (env);
}

char	*ft_getenv(char **env, char *env_name)
{
	int	i;
	int	env_len;

	if (!env || !(*env))
		return (NULL);
	i = 0;
	env_len = ft_strlen(env_name);
	while (env[i])
	{
		if (strncmp(env[i], env_name, env_len) == 0
			&& env[i][env_len] == '=')
			return (env[i] + env_len + 1);
		i++;
	}
	return (NULL);
}

char	*trim_free(char *str)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strtrim(str, " \t");
	free(tmp);
	return (str);
}

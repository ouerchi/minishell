/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_building_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:23:26 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 15:37:42 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**lst_to_array(t_env *env_lst)
{
	t_env	*current;
	int		i;
	int		j;
	char	**env;

	current = env_lst;
	j = 0;
	while (current)
	{
		j++;
		current = current->next;
	}
	if (!j)
		return (NULL);
	env = (char **)malloc(sizeof(char *) * (j + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (env_lst)
	{
		env[i++] = ft_strdup(env_lst->variable);
		env_lst = env_lst->next;
	}
	env[i] = NULL;
	return (env);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	update_env_array(t_config *config)
{
	char	**new_env;

	new_env = lst_to_array(config->env_lst);
	if (!new_env)
		return ;
	free_array(config->env);
	config->env = new_env;
}

static int	update_env_value(t_env **env, char *name, char *value)
{
	char	*variable;

	if (*env)
	{
		if (ft_strlen(name) == ft_strlen((*env)->name)
			&& !ft_strncmp(name, (*env)->name, ft_strlen(name)))
		{
			if (!value)
				return (1);
			free((*env)->value);
			free((*env)->variable);
			value = trim_free(value);
			(*env)->value = ft_strdup(value);
			variable = ft_strdup(name);
			variable = ft_strjoin(variable, "=");
			variable = ft_strjoin(variable, value);
			(*env)->variable = ft_strdup(variable);
			free(value);
			return (1);
		}
		else
			return (update_env_value(&((*env)->next), name, value));
	}
	return (0);
}

void	append_var_value(t_config *config, char *name_var, char *value)
{
	char	*name;
	char	*old_value;
	char	*new_value;
	// t_env	*env;
	
	name = NULL;
	name = ft_substr(name_var, 0, ft_strlen(name_var) - 1);
	if (!name)
		return ;
	// env = config->env_lst;
	old_value = ft_strdup(ft_getenv(config->env, name));
	if (!old_value)
		old_value = ft_strdup("");
	new_value = ft_strjoin(old_value, value);
	free(old_value);
	if (!new_value)
		return (free(name));
	ft_setenv(config, name, ft_strdup(new_value));
}

void	ft_setenv(t_config *config, char *name, char *value)
{
	char	*variable;

	if (!name)
		return ;
	if (ft_strchr(name, '+'))
		return (append_var_value(config, name, value));
	if (update_env_value(&(config->env_lst), name, value) == 1)
		return ;
	variable = ft_strdup(name);
	value = trim_free(value);
	if (value)
	{
		variable = ft_strjoin(variable, "=");
		variable = ft_strjoin(variable, value);
		free(value);
	}
	append_env_lst(&(config->env_lst), variable);
	free(variable);
}

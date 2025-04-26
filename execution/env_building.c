/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:47 by mouerchi          #+#    #+#             */
/*   Updated: 2025/04/26 16:13:08 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

/*---------------- build env list -------------------*/

char	**ft_split_var(char *variable)
{
	char	**splited_var;
	int		i;

	if (!variable)
		return (NULL);
	splited_var = (char **)malloc(sizeof(char *) * 2);
	if (!splited_var)
		return (NULL);
	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	if (!variable[i])
		return(free(splited_var), NULL);
	splited_var[0] = ft_substr(variable, 0, i);
	if (!splited_var[0])
		return (free(splited_var), NULL);
	i++;
	if (!variable[i])
		splited_var[1] = ft_strdup("");
	else
		splited_var[1] = ft_substr(variable, i, ft_strlen(variable));
	if (!splited_var[1])
		return (free(splited_var[0]), free(splited_var), NULL);
	return (splited_var);
}

void	free_env_lst(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		free(env->variable);
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_lst(t_env **lst)
{
	free_env_lst(*lst);
	*lst = NULL;
}

void	append_env_lst(t_env **lst, char *variable)
{
	t_env	*node;
	t_env	*current;
	char	**splited_var;

	if (!lst || !variable)
		return ;
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (free_lst(lst));
	splited_var = ft_split_var(variable);
	if (splited_var)
	{
		node->name = ft_strdup(splited_var[0]);
		node->value = ft_strdup(splited_var[1]);
	}
	else
	{
		node->name = ft_strdup(variable);
		node->value = NULL;
	}
	if (!(*lst))
	{
		*lst = node;
		return ;
	}
	current = *lst;
	while(current->next)
		current = current->next;
	current->next = node;
}


t_env	*get_env_lst(t_config *config)
{
	char	**env;
	int		i;
	t_env	*lst;

	env = config->env;
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

/*--------------- build env array -------------------*/
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
	i = -1;
	while (++i < count)
	{
		env[i] = real_env[i];
		if (!fail_check(&env, i))
			return (NULL);
	}
	env[count] = NULL;
	return (env);
}

/*--------------- check environment -------------------*/

char	*ft_getenv(char **env, char *env_name)
{
	int	i;
	int env_len;

	if (!env || !(*env))
		return (NULL);
	i = 0;
	env_len = ft_strlen(env_name);
	while(env[i])
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

// function to update the env list
int	update_env_value(t_env **env, char *name, char *value)
{
	char	*variable;

	if (*env)
	{
		if (ft_strlen(name) == ft_strlen((*env)->name) && !ft_strncmp(name, (*env)->name, ft_strlen(name)))
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
			(*env)->variable = variable;
			free(value);
			return (1);
		}
		else
			return (update_env_value(&((*env)->next), name, value));
	}
	return (0);

}


void	ft_setenv(t_config *config, char *name, char *value)
{
	char	*variable;

	if (!name)
		return ;
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

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**lst_to_array(t_env *env_lst)
{
	t_env	*current;
	int		i;
	char	**env;
	
	current = env_lst;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	if (!i)
		return (NULL);
	env = (char **)malloc(sizeof(char *) * i + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (env_lst)
	{
		env[i] = ft_strdup(env_lst->variable);	
		env_lst = env_lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	update_env(t_config *config)
{
	char	**new_env;

	new_env = lst_to_array(config->env_lst);
	if (!new_env)
		return ;
	free_array(config->env);
	config->env = new_env;
}

void	check_env(t_config *config)
{
	char	*tmp;
	int		shell_level;

	if (!ft_getenv(config->env, "PATH"))
		ft_setenv(config, "PATH",
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
		ft_setenv(config, "PWD", tmp);
	}
	update_env(config);

}

void	init_env(t_config *config, char **env)
{
	config->env = get_env(env);
	config->env_lst = NULL;
	config->env_lst = get_env_lst(config);
	check_env(config);
}
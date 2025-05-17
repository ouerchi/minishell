/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:34:50 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/16 16:14:22 by mouerchi         ###   ########.fr       */
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

void	msg_error(char *msg1, char *full, char *msg2)
{
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(full, 2);
	ft_putstr_fd(msg2, 2);
}

int	is_valid_char(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	// if ((c >= 33 && c <= 42) || (c >= 44 && c <= 47) || (c >= 58 && c <= 64))
	// 	return (0);
	return (1);
}

int	valid_var_name(char *name, char *full)
{
	int i;

	if (!name[0] || (!ft_isalpha(name[0])&& name[0] != '_'))
	{
		msg_error("minishell: export: `", full, "' : not a valid identifier\n");
		return (1);
	}
	i = 0;
	while (name[i] && name[i] != '+')
	{
		if (!is_valid_char(name[i]))
		{
			msg_error("minishell: export: `", full, "' : not a valid identifier\n");
			return (1);			
		}
		i++;
	}
	if (name[i] == '+' && name[i + 1] != '\0')
	{
		msg_error("minishell: export: `", full, "' : not a valid identifier\n");
		return (1);		
	}
	return (0);
}

int	export_args(t_config *config, char *arg, char *name)
{
	char	*value;
	char	*full;
	char	*equal_sign;

	(void)config;
	full = ft_strdup(arg);
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		name = arg;
		if (valid_var_name(name, full))
			return (free(full), free(arg), 1);
		value = equal_sign + 1;		
		ft_setenv(config, name, ft_strdup(value));
	}
	if (!equal_sign && !valid_var_name(arg, full))
		ft_setenv(config, arg, NULL);
	else if (!equal_sign)
		return (1);
	free(arg);
	return (0);
}

int	ft_export(t_config *config, char **args)
{
	char	**env;
	char	*name;
	int		i;

	name = NULL;
	env = config->env;
	if (!args[1])
		return (if_no_args(args, env));
	i = 1;
	while (args[i])
	{
		if (export_args(config, ft_strdup(args[i]), name))
			return (1);
		i++;
	}
	return (0);
}

/*

equal_pos = srch for '='

name =  

value = equal_pos + 1;


*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_building_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:22:18 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/16 15:53:27 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		return (free(splited_var), NULL);
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
		node->name = splited_var[0];
		node->value = splited_var[1];
	}
	else
	{
		node->name = ft_strdup(variable);
		node->value = NULL;
	}
	node->variable = ft_strdup(variable);
	node->next = NULL;
	free(splited_var);
	if (!(*lst))
	{
		*lst = node;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = node;
}

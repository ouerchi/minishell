/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:04 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/06 23:57:48 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_exp_par(char *buff, t_config *config, t_token *check)
{
	char	*value;
	char	*temp;

	value = ft_search_lst(config, buff + 1);
	if (value)
		temp = ft_strdup(value);
	else
		temp = ft_strdup(check->value);
	return (temp);
}

char	*ft_handle_no_in_q(t_config *config, t_token *check, int j)
{
	char	*buff;
	char	*temp;
	char	*temp_2;

	buff = ft_handle_words(check->value, j);
	if (check->value[0] == '$'
		&& (check->value[1] == '\'' || check->value[1] == '"'))
	{
		temp_2 = skip_char(buff, '$');
		temp = ft_strdup(temp_2);
		return (temp);
	}
	else if (check->value[0] == '\'' && check->value[1] == '$')
	{
		temp = ft_strdup(buff);
		return (temp);
	}
	else if (check->value[0] == '"' && check->value[1] == '$')
	{
		temp = ft_exp_par(buff, config, check);
		return (temp);
	}
	else
		return (NULL);
}

char	*ft_search_lst(t_config *config, char *buff)
{
	t_env	*tmp;

	tmp = config->env_lst;
	if (buff)
	{
		while (tmp)
		{
			if (f_strcmp(tmp->name, buff) == 0)
				return (ft_strdup(tmp->value));
			tmp = tmp->next;
		}
	}
	return (NULL);
}

int	ft_calc_dol(char *buff, int i)
{
	int	count;

	count = 0;
	while (buff[i] && buff[i++] == '$')
		count++;
	return (count);
}

char	*skip_char(char *str, char set)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == set)
		i++;
	return (str + i);
}

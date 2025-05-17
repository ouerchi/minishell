/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:04 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/13 18:40:08 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_queen(t_token *check, t_config *config, t_exp exp, t_q q)
{
	exp.flag = has_q(check->value);
	exp.count = ft_calc_dol(check->value, 0) % 2;
	if (exp.flag == 1 && exp.count == 1 && !has_doll_2(check->value))
		return (ft_strdup("$"));
	while (check->value[exp.j])
	{
		if (check->value[exp.j] == '\'' || check->value[exp.j] == '"')
			exp.res = second(check, exp, &exp.j, &q);
		else if (q.single_q == 0 && check->value[exp.j] == '$'
			&& is_numeric_char(check->value, exp.j + 1))
			exp.j += 2;
		else if (check->value[exp.j] == '$' && (check->value[exp.j + 1] == '\''
				|| check->value[exp.j + 1] == '"') && q.single_q == 0
			&& q.double_q == 0)
			exp.j++;
		else if (check->value[exp.j] == '$' && check->value[exp.j + 1] == '\0')
			exp.res = ft_strjoin_char(exp.res, check->value[exp.j++]);
		else if (check->value[exp.j] == '$' && check->value[exp.j + 1] != '\''
			&& check->value[exp.j + 1] != '"' && q.single_q == 0)
			exp.res = third(check, config, exp, &exp.j);
		else
			exp.res = ft_strjoin_char(exp.res, check->value[exp.j++]);
	}
	return (exp.res);
}

void	ft_quotes_exp(char *buff, int *i, t_q *quotes)
{
	if (buff[(*i)] == '"' && quotes->double_q == 1)
	{
		quotes->double_q = 0;
		(*i)++;
	}
	else if (buff[(*i)] == '"' && quotes->double_q == 0
		&& quotes->single_q == 0)
	{
		quotes->double_q = 1;
		(*i)++;
	}	
	else if (buff[(*i)] == '\'' && quotes->single_q == 1)
	{
		quotes->single_q = 0;
		(*i)++;
	}
	else if (buff[(*i)] == '\'' && quotes->single_q == 0
		&& quotes->double_q == 0)
	{
		quotes->single_q = 1;
		(*i)++;
	}
}

char	*merge_temp(char *buff, int *i, char *temp, t_q *quotes)
{
	while (buff[(*i)] == '"' || buff[(*i)] == '\'')
	{
		ft_quotes_exp(buff, i, quotes);
		if (quotes->double_q == 1)
		{
			while (buff[(*i)] && buff[(*i)] != '"' && buff[(*i)] == '\'')
				temp = ft_strjoin_char(temp, buff[(*i)++]);
			if (buff[(*i)] == '"')
			{
				(*i)++;
				quotes->double_q = 0;
			}
		}
		else if (quotes->single_q == 1)
		{
			while (buff[(*i)] && buff[(*i)] != '\'' && buff[(*i)] == '"')
				temp = ft_strjoin_char(temp, buff[(*i)++]);
			if (buff[(*i)] == '\'')
			{
				(*i)++;
				quotes->single_q = 0;
			}
		}
	}
	return (temp);
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

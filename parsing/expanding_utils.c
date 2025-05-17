/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:04 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 00:59:43 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_queen(char *buff, t_config *config, t_exp exp, t_q q)
{
	exp.count = ft_calc_dol(buff, 0) % 2;
	if (has_q(buff) == 1 && exp.count == 1 && !has_doll_2(buff))
		return (ft_strdup("$"));
	while (buff[exp.j])
	{
		if (buff[exp.j] == '\'' || buff[exp.j] == '"')
			exp.res = second(buff, exp, &exp.j, &q);
		else if (q.single_q == 0 && buff[exp.j] == '$'
			&& is_numeric_char(buff, exp.j + 1))
			exp.j += 2;
		else if (buff[exp.j] == '$' && (buff[exp.j + 1] == '\''
				|| buff[exp.j + 1] == '"') && q.single_q == 0
			&& q.double_q == 0)
			exp.j++;
		else if (buff[exp.j] == '$' && buff[exp.j + 1] == '\0')
			exp.res = ft_strjoin_char(exp.res, buff[exp.j++]);
		else if (buff[exp.j] == '$' && buff[exp.j + 1] != '\''
			&& buff[exp.j + 1] != '"' && q.single_q == 0
			&& (ft_isalnum(buff[exp.j + 1]) || buff[exp.j + 1] == '_'
				|| buff[exp.j + 1] == '$'))
			exp.res = third(buff, config, exp, &exp.j);
		else
			exp.res = ft_strjoin_char(exp.res, buff[exp.j++]);
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

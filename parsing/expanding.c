/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:48:41 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/07 23:49:19 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expanding(t_token *check, t_config *config)
{
	int			j;
	t_exp		exp;
	t_quotes	quotes;

	j = 0;
	exp.res = NULL;
	quotes.double_q = 0;
	quotes.single_q = 0;
	exp.count = ft_calc_dol(check->value, j) % 2;
	while (check->value[j])
	{
		if (j == 0)
		{
			exp.res = ft_handle_no_in_q(config, check, j);
			if (exp.res)
				return (exp.res);
		}
		if (check->value[j] == '\'' || check->value[j] == '"')
		{
			exp.temp = merge_temp(check->value, &j, NULL, &quotes);
			exp.res = ft_strjoin_free(exp.res, exp.temp);
		}
		else if (quotes.single_q == 0 && check->value[j] == '$'
			&& is_numeric_char(check->value, j + 1))
			j += 2;
		else if (check->value[j] == '$' && quotes.single_q == 0
			&& exp.count != 0)
		{
			exp.temp_var = ft_handle_name(check->value, &j);
			exp.temp_val = ft_search_lst(config, exp.temp_var);
			exp.res = ft_strjoin_free(exp.res, exp.temp_val);
			free(exp.temp_var);
		}
		else
			exp.res = ft_strjoin_char(exp.res, check->value[j++]);
	}
	return (exp.res);
}

void	ft_quotes_exp(char *buff, int *i, t_quotes *quotes)
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

char	*merge_temp(char *buff, int *i, char *temp, t_quotes *quotes)
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

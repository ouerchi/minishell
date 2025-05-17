/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:24:18 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/13 19:04:50 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_doll_2(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '$')
		i++;
	if (!str[i])
		return (0);
	return (1);
}

char	*second(t_token *check, t_exp exp, int *j, t_q *quotes)
{
	exp.temp = merge_temp(check->value, j, NULL, quotes);
	exp.res = ft_strjoin_free(exp.res, exp.temp);
	return (exp.res);
}

char	*third(t_token *check, t_config *config, t_exp exp, int *j)
{
	exp.temp_var = ft_handle_name(check->value, j);
	exp.temp_val = ft_search_lst(config, exp.temp_var);
	exp.res = ft_strjoin_free(exp.res, exp.temp_val);
	free(exp.temp_var);
	return (exp.res);
}

void	init_queen(t_exp *exp, t_q *quotes)
{
	exp->j = 0;
	exp->res = NULL;
	quotes->double_q = 0;
	quotes->single_q = 0;
}

int	ft_calc_dol(char *buff, int i)
{
	int	count;

	count = 0;
	while (buff[i] == '$')
	{
		count++;
		i++;
	}
	return (count);
}

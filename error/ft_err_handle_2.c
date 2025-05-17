/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_handle_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:44:40 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/10 16:11:17 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_quotes_state	ft_handle_quotes(char *rl)
{
	int				i;
	t_quotes_state	state;

	i = 0;
	state = NONE;
	while (rl[i])
	{
		if (rl[i] == '\\' && state != S_QUOTES)
		{
			i++;
			continue ;
		}
		if (state == NONE)
		{
			if (rl[i] == '\'')
				state = S_QUOTES;
			else if (rl[i] == '"')
				state = D_QUOTES;
		}
		else if ((state == S_QUOTES && rl[i] == '\'')
			|| (state == D_QUOTES && rl[i] == '"'))
			state = NONE;
		i++;
	}
	return (state);
}

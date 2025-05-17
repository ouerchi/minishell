/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:44:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/13 19:01:36 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_q(char *del)
{
	int	i;

	i = 0;
	while (del[i])
	{
		if (del[i] == '\'' || del[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

int	validate_pipes_her(t_token *token, int *count_per)
{
	int		expect_command;

	expect_command = 1;
	while (token)
	{
		if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
			|| token->type == T_APPEND || token->type == T_HERDOC)
		{
			if (ft_if(token) == 0)
				return (0);
		}
		else if (token->type == T_PIPE)
		{
			if (expect_command)
				return (0);
			(*count_per)++;
			expect_command = 1;
		}
		else
			expect_command = 0;
		token = token->next;
	}
	if (expect_command)
		return (0);
	return (1);
}

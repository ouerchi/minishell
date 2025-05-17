/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:11:21 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 18:34:03 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_pipes(t_token *token, t_config *config)
{
	int		flag;
	int		expect_command;
	t_token	*next_token;

	flag = 0;
	expect_command = 1;
	while (token)
	{
		if (token->next && token->type == T_HERDOC && token->next->type == T_WORD && flag == 0)
		{
			if (hna_her(config, token, &flag) == 0)
				return (-1);
		}
		if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT || token->type == T_APPEND || token->type == T_HERDOC)
		{
			next_token = token->next;
			if (!next_token)
				return (printf("minishell: syntax error near unexpected token 'newline'\n"), 0);
			else if (next_token->type == T_PIPE)
				return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
			else if (next_token->type == T_REDIR_IN || next_token->type == T_REDIR_OUT || next_token->type == T_APPEND || next_token->type == T_HERDOC)
				return (printf("minishell: syntax error near unexpected token '%s'\n", next_token->value), 0);
		}
		else if (token->type == T_PIPE)
		{
			if (expect_command)
				return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
			expect_command = 1;
		}
		else
			expect_command = 0;
		token = token->next;
	}
	return (1);
}

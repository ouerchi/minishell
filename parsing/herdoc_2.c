/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:44:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 02:48:19 by azaimi           ###   ########.fr       */
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

int	ft_if_2(t_token *token, t_her *her)
{
	if (token->type == T_HERDOC)
		her->count_per++;
	if (ft_if(token) == 0)
		return (0);
	return (1);
}

int	validate_pipes_her(t_token *token, t_her *her)
{
	int		expect_command;

	expect_command = 1;
	while (token)
	{
		if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
			|| token->type == T_APPEND || token->type == T_HERDOC)
		{
			if (ft_if_2(token, her) == 0)
				return (0);
		}
		else if (token->type == T_PIPE)
		{
			if (expect_command)
				return (0);
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

int	ft_strcmp_her(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	if (!s1 || !s2)
		return (INT_MIN);
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while ((p1[i] || p2[i]))
	{
		if (p1[i] != p2[i])
		{
			if (p1[i] > p2[i])
				return (1);
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

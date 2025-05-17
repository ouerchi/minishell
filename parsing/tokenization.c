/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:43:49 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/10 16:12:16 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handle_word(char *rl, int *i, t_token **lst)
{
	char	*buff;

	buff = ft_handle_buff(rl, i);
	if (buff)
	{
		ft_lstadd_back_token(lst, ft_token_new(T_WORD, buff));
		free(buff);
		buff = NULL;
	}
}

void	ft_handle_redir_in(char *rl, int *i, t_token **lst)
{
	if (rl[(*i) + 1] == '<')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_HERDOC, "<<"));
		(*i) += 2;
	}
	else if (rl[(*i) + 1] == '>')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_IN, "<>"));
		(*i) += 2;
	}
	else
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_IN, "<"));
		(*i)++;
	}
}

void	ft_handle_redir_out(char *rl, int *i, t_token **lst)
{
	if (rl[(*i) + 1] == '|')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_OUT, ">|"));
		(*i) += 2;
	}
	else if (rl[(*i) + 1] == '>')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_APPEND, ">>"));
		(*i) += 2;
	}
	else
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_OUT, ">"));
		(*i)++;
	}
}

void	process_char(char *rl, int *i, t_token **lst)
{
	if (!ft_strchr(">|<", rl[(*i)]))
		ft_handle_word(rl, i, lst);
	else if (rl[(*i)] == '<')
		ft_handle_redir_in(rl, i, lst);
	else if (rl[(*i)] == '>')
		ft_handle_redir_out(rl, i, lst);
	else if (rl[(*i)] == '|')
	{
		(*i)++;
		ft_lstadd_back_token(lst, ft_token_new(T_PIPE, "|"));
	}
	else
		(*i)++;
}

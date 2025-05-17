/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:43:49 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 00:58:28 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handle_word_2(t_token **lst, t_config *config, t_h_w *h_w)
{
	if (h_w->temp[0] != '\0')
	{
		h_w->temp_2 = ft_split(h_w->temp, " ");
		while (h_w->temp_2[h_w->j])
			ft_lstadd_back_token(lst, \
				ft_token_new(T_WORD, h_w->temp_2[h_w->j++], h_w->buff));
		config->amb = h_w->j;
	}
	else
	{
		config->flag_2 = 1;
		ft_lstadd_back_token(lst, ft_token_new(T_WORD, h_w->temp, h_w->buff));
	}
}

void	ft_handle_word(char *rl, int *i, t_token **lst, t_config *config)
{
	t_h_w	h_w;

	h_w.j = 0;
	h_w.flag = 0;
	h_w.buff = ft_handle_buff(rl, i);
	h_w.q = has_q(h_w.buff);
	h_w.temp = ft_word(h_w.buff, config, &h_w.flag);
	if (h_w.temp)
	{
		if (h_w.flag == 1 && h_w.q == 1)
			ft_handle_word_2(lst, config, &h_w);
		else
		{
			ft_lstadd_back_token(lst, ft_token_new(T_WORD, h_w.temp, h_w.buff));
			free(h_w.temp);
			h_w.temp = NULL;
		}
	}
}

void	ft_handle_redir_in(char *rl, int *i, t_token **lst)
{
	if (rl[(*i) + 1] == '<')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_HERDOC, "<<", NULL));
		(*i) += 2;
	}
	else if (rl[(*i) + 1] == '>')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_IN, "<>", NULL));
		(*i) += 2;
	}
	else
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_IN, "<", NULL));
		(*i)++;
	}
}

void	ft_handle_redir_out(char *rl, int *i, t_token **lst)
{
	if (rl[(*i) + 1] == '|')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_OUT, ">|", NULL));
		(*i) += 2;
	}
	else if (rl[(*i) + 1] == '>')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_APPEND, ">>", NULL));
		(*i) += 2;
	}
	else
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_OUT, ">", NULL));
		(*i)++;
	}
}

void	process_char(char *rl, int *i, t_token **lst, t_config *config)
{
	if (!ft_strchr(">|<", rl[(*i)]))
		ft_handle_word(rl, i, lst, config);
	else if (rl[(*i)] == '<')
		ft_handle_redir_in(rl, i, lst);
	else if (rl[(*i)] == '>')
		ft_handle_redir_out(rl, i, lst);
	else if (rl[(*i)] == '|')
	{
		(*i)++;
		ft_lstadd_back_token(lst, ft_token_new(T_PIPE, "|", NULL));
	}
	else
		(*i)++;
}

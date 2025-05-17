/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:23:31 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/15 21:45:21 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_buff(char *rl, int *i)
{
	char	*buff;
	char	quote;

	buff = NULL;
	while (rl[*i] && !ft_strchr(" >|<", rl[*i]))
	{
		if (rl[*i] == '\'' || rl[*i] == '"')
		{
			quote = rl[*i];
			buff = ft_strjoin_char(buff, quote);
			(*i)++;
			while (rl[*i] && rl[*i] != quote)
				buff = ft_strjoin_char(buff, rl[(*i)++]);
			if (rl[*i] == quote)
			{
				buff = ft_strjoin_char(buff, quote);
				(*i)++;
			}
		}
		else
			buff = ft_strjoin_char(buff, rl[(*i)++]);
	}
	return (buff);
}

int	handle_char(t_dec *dec, char *rl, int *i)
{
	if (!dec->quote && (rl[*i] == '\'' || rl[*i] == '"'))
	{
		dec->quote = rl[(*i)++];
		return (1);
	}
	if (dec->quote && rl[*i] == dec->quote)
	{
		dec->quote = 0;
		(*i)++;
		return (1);
	}
	if (!dec->quote && ft_strchr(">|< \t", rl[*i]))
		return (0);
	dec->temp = ft_strjoin_char(dec->buff, rl[(*i)++]);
	if (!dec->temp)
		return (0);
	free(dec->buff);
	dec->buff = dec->temp;
	return (1);
}

char	*ft_handle_words(char *rl, int i)
{
	t_dec	dec;

	dec.quote = 0;
	dec.buff = NULL;
	while (rl[i])
	{
		if (!handle_char(&dec, rl, &i))
			break ;
	}
	return (dec.buff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:48:41 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/13 19:03:52 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_word(t_token *check, t_config *config)
{
	char	*dup;
	t_exp	exp;
	t_q		quotes;

	if (has_doll(check->value) == 0)
	{
		init_queen(&exp, &quotes);
		dup = ft_queen(check, config, exp, quotes);
	}
	else
		dup = ft_handle_words(check->value, 0);
	return (dup);
}

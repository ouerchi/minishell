/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:48:41 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/16 20:49:17 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_word(char *buff, t_config *config, int *flag)
{
	char	*dup;
	t_exp	exp;
	t_q		quotes;

	if (has_doll(buff) == 0)
	{
		(*flag) = 1;
		init_queen(&exp, &quotes);
		dup = ft_queen(buff, config, exp, quotes);
	}
	else
		dup = ft_handle_words(buff, 0);
	if (dup == NULL)
		dup = ft_strdup("");
	return (dup);
}

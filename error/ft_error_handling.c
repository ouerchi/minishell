/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:12:25 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/07 00:21:59 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_error_type	ft_handle_error(char *rl)
{
	t_quotes_state	state_quotes;

	state_quotes = ft_handle_quotes(rl);
	if (state_quotes != NONE)
		return (ERR_UNCLOSED_QUOTES);
	return (ERR_NONE);
}

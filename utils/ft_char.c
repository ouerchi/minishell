/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:53:54 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/10 16:12:49 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric_char(char *str, int i)
{
	if (!str || *str == '\0')
		return (0);
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	return (0);
}

int	ft_isdigit(int ch)
{
	if (ch >= 48 && ch <= 57)
		return (1);
	return (0);
}

int	ft_isalpha(int ch)
{
	if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
		return (1);
	return (0);
}

int	ft_isalnum(int ch)
{
	if (ft_isdigit(ch) == 1 || ft_isalpha(ch) == 1)
		return (1);
	return (0);
}

int	is_alpha_char(char *str, int i)
{
	if (!str || *str == '\0')
		return (0);
	if ((str[i] < 'a' && str[i] > 'z') || (str[i] < 'A' && str[i] > 'Z'))
		return (0);
	return (1);
}

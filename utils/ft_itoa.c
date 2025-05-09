/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:42 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/06 23:13:44 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	digit_count(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count = 1;
		n = n * -1;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static int	converte(char *ascii, int n, int i)
{
	if (n >= 10)
	{
		i = converte(ascii, n / 10, i);
	}
	ascii[i] = (n % 10) + '0';
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*ascii;
	int		i;

	i = 0;
	if (n == -2147483648 || n == 0)
	{
		if (n == 0)
			return (ft_strdup("0"));
		else
			return (ft_strdup("-2147483648"));
	}
	ascii = malloc(digit_count(n) + 1);
	if (ascii == NULL)
		return (NULL);
	if (n < 0)
	{
		ascii[0] = '-';
		n = -n;
		i = 1;
	}
	i = converte(ascii, n, i);
	ascii[i] = '\0';
	return (ascii);
}

static long	calc_result(long tmp, long result, char c, int sign)
{
	tmp = (result * 10) + (c - 48);
	if (tmp < result && sign == 1)
		return (-1);
	else if (tmp < result && sign == -1)
		return (0);
	return (tmp);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;
	long	tmp;

	i = 0;
	sign = 1;
	result = 0;
	tmp = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = calc_result(tmp, result, str[i], sign);
		i++;
	}
	return (sign * result);
}

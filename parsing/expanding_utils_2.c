/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:57:18 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/06 23:58:42 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_name(char *buff, int *i)
{
	char	*temp;

	temp = NULL;
	(*i)++;
	while (buff[(*i)] && (ft_isalnum(buff[(*i)]) || buff[(*i)] == '_'))
		temp = ft_strjoin_char(temp, buff[(*i)++]);
	return (temp);
}

char	*ft_handle_num_dol(char *buff, int *i)
{
	char	*temp;

	temp = NULL;
	(*i) += 2;
	while (buff[(*i)] && (ft_isalnum(buff[(*i)]) || buff[(*i)] == '_'))
		temp = ft_strjoin_char(temp, buff[(*i)++]);
	return (temp);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	free(s1);
	free(s2);
	return (new_str);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}

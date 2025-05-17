/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 03:10:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/16 22:28:59 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_files(t_parse **p, t_files *new)
{
	t_files	*tmp;

	if (!new)
		return ;
	if (!*p)
	{
		*p = malloc(sizeof(t_parse));
		if (!(*p))
			return ;
		(*p)->file = new;
		(*p)->file->next = NULL;
		return ;
	}
	if (!(*p)->file)
	{
		(*p)->file = new;
		return ;
	}
	tmp = (*p)->file;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

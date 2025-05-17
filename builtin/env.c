/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:59:02 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/10 16:11:37 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *env_lst)
{
	t_env	*tmp;

	if (!env_lst)
		return (1);
	tmp = env_lst;
	while (tmp)
	{
		printf("%s\n", tmp->variable);
		tmp = tmp->next;
	}
	return (0);
}

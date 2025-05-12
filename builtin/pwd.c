/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:15:26 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/10 14:55:34 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_config *config)
{
	char *cwd;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		printf("%s\n", ft_getenv(config->env, "PWD"));
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free (cwd);
	return (0);
}

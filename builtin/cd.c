/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:59:18 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/04 15:43:57 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cd_error(void)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

int	goto_home_dir(char **env)
{
	int		res;
	char	*env_value;
	
	char	*env_value;

	env_value = ft_getenv(env, "HOME");
	if (!env_value)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	res = chdir(env_value);
	if (res < 0)
	{
		print_cd_error();
		return (1);
	}
	return (0);
}

int	goto_prev_dir(char **env)
{
	int	res;
	char	*env_value;

	env_value = ft_getenv(env, "OLDPWD");
	if (!env_value)
	{
		ft_putstr_fd("cd: OLDPWD not set", 2);
		return (1);
	}
	res = chdir(env_value);
	if (res < 0)
	{
		print_cd_error();
		return (1);
	}
	return (0);
}

int ft_cd(char *path, char **env)
{
	char	*cwd;
	int		cd_rtrn;

	if (!path)
		return (goto_home_dir(env));
	cwd = getcwd(NULL, 0);
	if (!cwd && ft_strcmp(path, "..") )
	{
		
		return (-1);
	}
	if (ft_strcmp(path, "-") == 0)
		cd_rtrn = goto_prev_dir(env);
	else
	{
		cd_rtrn = chdir(path);
		if (cd_rtrn < 0)
		{
			free(cwd);
			print_cd_error();
			return(1);
		}
	}
	free(cwd);
	return (0);
}


// int main()
// {
// 	char *str;
// 	char cwd[100];

// 	str = "..";
// 	printf("%s\n", getcwd(cwd, 100));
// 	ft_cd(str);
// 	printf("%s\n", getcwd(cwd, 100));

// }
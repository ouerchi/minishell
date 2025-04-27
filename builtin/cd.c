/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:59:18 by mouerchi          #+#    #+#             */
/*   Updated: 2025/04/27 13:11:04 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_option(int option, char **env_value, char **env)
{
	if (option == CD_HOME)
	{
		*env_value = ft_getenv(env, "HOME");
		if (!(*env_value))
			return (1);
	}
	return (0);
}

int	cd_directory(int option, char **env)
{
	int		res;
	char	*env_value;
	
	if (check_option(option, &env_value, env))
		return (-1);
	res = chdir(env_value);
	if (!res)
		// return an error msg;
	return (0);
}

int ft_cd(char *str, char **env)
{
	if (!str)
		return (cd_directory(CD_HOME, env));
	
	// absolute path : cd /home/desktop...
	// relative path : cd desktop
	// parent directory : cd ..
	// multiple directories : cd ../../..
}


int main()
{
	char *str;
	char cwd[100];

	str = "..";
	printf("%s\n", getcwd(cwd, 100));
	ft_cd(str);
	printf("%s\n", getcwd(cwd, 100));

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:59:18 by mouerchi          #+#    #+#             */
/*   Updated: 2025/04/26 17:59:25 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>




int ft_cd(char *str, char **env)
{
	// empty cd : change to home directory : cd
		// if !str
			// cd home
			// use 

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
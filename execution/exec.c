/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:30:37 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 17:11:05 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_handling(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	get_path(t_config *config, t_parse *cmd)
{
	if (is_file(cmd->cmd_name) || is_path(cmd->cmd_name))
	{
		if (access(cmd->cmd_name, F_OK) != 0)
			error_handling(cmd->cmd_name, ": No such file or directory");
		if (access(cmd->cmd_name, X_OK) != 0)
			error_handling(cmd->cmd_name, ": Permission denied");
		config->path = ft_strdup(cmd->cmd_name);
	}
	else
	{
		config->path = find_path(cmd->cmd_name, config->env);
		if (!config->path)
			error_handling(cmd->cmd_name, ": No such file or directory");
	}
}

void	execute_cmd(t_config *config, t_parse *cmd)
{
	if (is_directory(cmd->cmd_name))
	{
		msg_error("minishell : ", cmd->cmd_name, ": Is a directory\n");
		exit(126);
	}
	get_path(config, cmd);
	execve(config->path, cmd->args, config->env);
	perror(cmd->cmd_name);
	exit(1);
}

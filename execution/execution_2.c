/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:34:33 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 15:39:14 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent(t_config *config)
{
	close(config->saved_fd);
	while (waitpid(-1, NULL, 0) != -1)
		;
}

void	init_process(t_config *config)
{
	config->cmd_idx = 0;
	config->saved_fd = -1;
}

void	safe_close(int	*fd)
{
	if ((*fd) >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

int	redir_in(t_parse *cmd, char *file_name)
{
	safe_close(&cmd->infile);
	cmd->infile = open(file_name, O_RDONLY);
	if (cmd->infile == -1)
		return (perror(file_name), -1);
	return (0);
}

int	redir_out(t_parse *cmd, char *file_name)
{
	if (is_directory(file_name))
		return (msg_error("minishell: ", file_name, ": Is a directory"), 1);
	safe_close(&cmd->outfile);
	cmd->outfile = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		return (perror(file_name), -1);
	return (0);
}

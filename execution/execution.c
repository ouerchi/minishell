/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:05:13 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/17 20:22:47 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_io(t_config *config, t_parse *cmd)
{
	if (cmd->next)
	{
		close(config->pipe[0]);
		if (dup2(config->pipe[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(config->pipe[1]);
	}
	if (config->saved_fd != -1)
	{
		if (dup2(config->saved_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(config->saved_fd);
	}
	if (cmd->infile != -1 && cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			perror("dup2");
		close(cmd->infile);
	}
	if (cmd->outfile != -1 && cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmd->outfile);
	}
}

void	run_child_process(t_config *config, t_parse *cmd)
{
	redirect_io(config, cmd);
	if (cmd->builtins == 1)
	{
		run_builtins(config, cmd);
		exit(0) ;
	}
	execute_cmd(config, cmd);
}

static int	open_files(t_parse *head_cmd)
{
	t_parse	*cmd;
	t_files	*file;

	cmd = head_cmd;
	while (cmd)
	{
		cmd->infile = -1;
		cmd->outfile = -1;
		file = cmd->file;
		while (file)
		{
			if (file->name && f_strcmp(file->type, "REDIR_IN") == 0)
			{
				if (redir_in(cmd, file->name) == -1)
					return (-1);
			}
			else if (file->name && f_strcmp(file->type, "REDIR_OUT") == 0)
			{
				if (redir_out(cmd, file->name) == -1)
					return (-1);
			}
			else if (file->name && f_strcmp(file->type, "APPEND") == 0)
			{
				if (redir_append(cmd, file->name) == -1)
					return (-1);
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	run_builtins(t_config *config, t_parse *cmd)
{
	char	*tmp;
	int		status;

	if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
		status = ft_exit(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])))
	{
		tmp = array_join(&cmd->args[1]);
		status = ft_echo(tmp);
		free(tmp);
	}
	else if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])))
	{
		status = ft_export(config, cmd->args);
		update_env_array(config);
	}
	else
		status = run_builtins_rest(config, cmd);
	return (status);
}

void	apply_redir(t_parse *cmd)
{
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmd->outfile);
	}
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmd->infile);
	}
}
void	restore_redir(t_config *config)
{
	dup2(config->std_in, STDIN_FILENO);
	dup2(config->std_out, STDOUT_FILENO);
	close(config->std_in);
	close(config->std_out);
}

int	run_single_cmd(t_config *config)
{
	int		status;
	t_parse	*cmd;

	cmd = config->cmd;
	if (cmd->builtins)
	{
		config->std_in = dup(STDIN_FILENO);
		config->std_out = dup(STDOUT_FILENO);
		apply_redir(cmd);
		status = run_builtins(config, cmd);
		restore_redir(config);
		return (status);
	}
	status = spawn_child_process(config, cmd);
	parent(config);
	return (status);
}

int	execution(t_config *config)
{
	int		cmd_nmbr;
	t_parse	*current_cmd;

	init_process(config);
	cmd_nmbr = ft_cmd_nmbr(config->cmd);
	if (open_files(config->cmd) == -1)
		return (1);
	if (cmd_nmbr == 1)
		return (run_single_cmd(config));
	current_cmd = config->cmd;
	while (current_cmd && config->cmd_idx < cmd_nmbr)
	{
		spawn_child_process(config, current_cmd);
		current_cmd = current_cmd->next;
		config->cmd_idx++;
	}
	parent(config);
	return (0);
}

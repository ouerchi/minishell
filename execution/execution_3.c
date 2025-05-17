/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:34:07 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 15:38:27 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_nmbr(t_parse *cmd_lst)
{
	t_parse	*current;
	int		count_cmd;

	current = cmd_lst;
	count_cmd = 0;
	while (current)
	{
		count_cmd++;
		current = current->next;
	}
	return (count_cmd);
}

char	*array_join(char **str)
{
	char	*rtrn;
	int		i;

	i = 0;
	rtrn = ft_strdup("");
	while (str[i])
	{
		if (i > 0)
			rtrn = ft_strjoin(rtrn, " ");
		rtrn = ft_strjoin(rtrn, str[i]);
		i++;
	}
	return (rtrn);
}

int	check_option(char **args)
{
	if (!args[1])
		return (0);
	if (args[1][0] != '-')
		return (0);
	return (1);
}

int	run_builtins_rest(t_config *config)
{
	int		status;
	// char	*cwd;
	t_parse	*cmd;

	// cwd = NULL;
	cmd = config->cmd;
	status = 0;
	if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])))
	{
		status = ft_unset(config, cmd->args);
		update_env_array(config);
	}
	else if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])))
	{
		if (check_option(cmd->args))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("invalid option\n", 2);
			return (2);
		}
		status = ft_pwd(config);
	}
	else if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])))
		status = ft_env(config->env_lst);
	else if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
	{
		status = ft_cd(cmd->args[1], (config)->env);
	}
	return (status);
}

int	spawn_child_process(t_config *config, t_parse *cmd)
{
	pid_t	pid;

	if (cmd->next)
	{
		if (pipe(config->pipe) == -1)
		perror("pipe cmd");
	}
	
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
	}
	if (pid == 0)
		run_child_process(config, cmd);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	close(config->saved_fd);
	if (cmd->next)
	{
		config->saved_fd = dup(config->pipe[0]);
		if (config->saved_fd == -1)
			perror("dup pipe[0]");
	}
	if (cmd->next)
	{
		close(config->pipe[1]);
		close(config->pipe[0]);
	}
	return (0);
}

int	redir_append(t_parse *cmd, char *file_name)
{
	if (is_directory(file_name))
		return (msg_error("minishell: ", file_name, ": Is a directory"), 1);
	safe_close(&cmd->outfile);
	cmd->outfile = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->outfile == -1)
		return (perror(file_name), -1);
	return (0);
}

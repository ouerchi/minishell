/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:05:13 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/09 22:34:55 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static void	run_child_process(t_config *config, t_parse *cmd)
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
	execute_cmd(config, cmd);
}

int	spawn_child_process(t_config *config, t_parse *cmd)
{
	pid_t pid;

	if (cmd->next)
		pipe(config->pipe);
	pid = fork();
	if (pid == 0)
		run_child_process(config, cmd);
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

static void	parent(t_config *config)
{
	close(config->saved_fd);
	while(waitpid(-1, NULL, 0) != -1)
		;
}

static void	init_process(t_config *config)
{
	config->cmd_idx = 0;
	config->saved_fd = -1;
}

static void	safe_close(int	*fd)
{
	if ((*fd) >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

static int	redir_in(t_parse *cmd, char *file_name)
{
	safe_close(&cmd->infile);
	cmd->infile = open(file_name, O_RDONLY);
	if (cmd->infile == -1)
		return (perror(file_name), -1);
	return (0);
}

static int	redir_out(t_parse *cmd, char *file_name)
{
	safe_close(&cmd->outfile);
	cmd->outfile = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		return (perror(file_name), -1);
	return (0);
}

static int	redir_append(t_parse *cmd, char *file_name)
{
	safe_close(&cmd->outfile);
	cmd->outfile = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->outfile == -1)
		return (perror(file_name), -1);
	return (0);
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

static int ft_cmd_nmbr(t_parse *cmd_lst)
{
	t_parse *current;
	int count_cmd;

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

static int	run_builtins_rest(t_config *config)
{
	int			status;
	char		*cwd;
	t_parse	*cmd;

	cwd = NULL;
	cmd = config->cmd;
	status = 0;
	if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])))
	{
		status = ft_unset(config, cmd->args);
		update_env(config);
	}
	else if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])))
		status = ft_pwd(config);
	else if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])))
		status = ft_env(config->env_lst);
	else if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
	{
		status = ft_cd(cmd->args[1], (config)->env);
	}
	return (status);
}

int	run_builtins(t_config *config)
{
	t_parse	*cmd;
	char	*tmp;
	int		status;

	cmd = config->cmd;
	if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
		status = ft_exit(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])))
	{
		tmp = array_join(&cmd->args[1]);
		status = ft_echo(tmp);
		free(tmp);
	}
	// else if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])))
	// {
	// 	status = ft_export(config, cmd->args);
	// 	update_env(config);
	// }
	else
		status = run_builtins_rest(config);
	return (status);
}

int	check_cmd_type(t_config *config)
{
	t_parse	*cmd;

	cmd = config->cmd;
	if (cmd->builtins)
		return (run_builtins(config));
	int status = spawn_child_process(config, cmd);
	parent(config);
	return (status);
}

int	execution(t_config *config)
{
	int cmd_nmbr;
	t_parse		*current_cmd;

	init_process(config);
	cmd_nmbr = ft_cmd_nmbr(config->cmd);
	if (open_files(config->cmd) == -1)
		return (1);
	if (cmd_nmbr == 1)
		return (check_cmd_type(config));
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

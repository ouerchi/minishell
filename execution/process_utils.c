/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:15:25 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/02 14:23:29 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int dup_in(t_config *config)
{
	/*
	first cmd:
		infile or stdin = infile != -2 ? infile : stdin
		outfile or pipe = outfile != -2 ? outfile : pipe[1]
	
	last cmd
	*/
	t_parse *cmd;

	cmd = config->cmd;
	if (cmd->infile != -2)
	{
		if (dup2(cmd->infile, 1) == -1)
			/*return error*/ ;
		close(cmd->infile);
	}
}

char	*get_path_dirs(t_list *env)
{
	int i;
	char *str;

	i = 0;
	while (env)
	{
		while (env->content && env->content[i] != '=')
			i++;
		*str = ft_substr(env->content, 0, i);
		if (!ft_strcmp(str, "PATH"))
			return(str + i + 1);
		env = env->next;
	}
}

int ft_cmd_nmbr(t_parse *cmd_lst)
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

void	first_cmd(t_process *process, int in)
{
	t_parse *exec_cmd;

	exec_cmd = process->exec_cmd;
	if (in)
	{
		if (dup2(in, 0) == -1)
			/*return error*/;
		close(in);
	}
}

void	last_cmd(t_process *process, int out)
{
	t_parse *exec_cmd;
	if (out)
	{
		if (dup2(out, 1) == -1)
			/*return error*/;
		close(out);
	}
}


int	redirection_in(t_parse *cmd)
{
	if(cmd->in_re != -2)
		return (exec_cmd->in_re);
	else if (process->saved_fd != -1)
		return (process->saved_fd);
	return (0);
}

int redirection_out(t_process *process)
{
	t_parse *exec_cmd;

	exec_cmd = process->exec_cmd;
	if (exec_cmd->out_re != -2)
		return (exec_cmd->out_re);
	else if (process->pipe[1])
		return (process->pipe[1]);
	return (1);
}

void	ft_close_in(t_process *process)
{
	if (process->exec_cmd->in_re != -2)
		close(process->exec_cmd->in_re);
	if (process->saved_fd != -1)
		close(process->saved_fd);
}

void	ft_close_out(t_process *process)
{
	if (process->exec_cmd->out_re != -2)
		close(process->exec_cmd->out_re);
	close(process->pipe[1]);
}
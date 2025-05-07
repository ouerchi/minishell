

#include "../minishell.h"

// first cmd
// redir_in : file | stdin
// redir_out : file | pipe
// check if there's files : open them 

// last cmd
// redir_in : pipe
// redir_out : file | stdout

// other cmd
// redir_in : pipe | file
// redir_out : file | pipe






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

static void	spawn_child_process(t_config *config, t_parse *cmd)
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

static int	redir_in(t_parse *cmd)
{
	int	new_fd;
	new_fd = open(cmd->file->name, O_RDONLY);
	if (cmd->infile == -1)
	return (perror(cmd->file->name), -1);
	safe_close(&cmd->infile);
	cmd->infile = new_fd;
	return (0);
}

static int	redir_out(t_parse *cmd)
{
	printf("1: %s\n", cmd->file->name);
	// safe_close(&cmd->outfile);
	cmd->outfile = open(cmd->file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		return (perror(cmd->file->name), -1);
	// printf("2: %d\n", cmd->outfile);
	
	return (0);
}

static int	redir_append(t_parse *cmd)
{
	int	new_fd;
	new_fd = open(cmd->file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->outfile == -1)
		return (perror(cmd->file->name), -1);
	safe_close(&cmd->outfile);
	cmd->infile = new_fd;
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
			if (file->name && ft_strcmp(file->type, "REDIR_IN") == 0)
			{
				if (redir_in(cmd) == -1)
					return (-1);
			}
			else if (file->name && ft_strcmp(file->type, "REDIR_OUT") == 0)
			{
				if (redir_out(cmd) == -1)
					return (-1);
			}
			else if (file->name && ft_strcmp(file->type, "APPEND") == 0)
			{
				if (redir_append(cmd) == -1)
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

void	execution(t_config *config)
{
	pid_t	pid;
	int cmd_nmbr;
	t_parse		*current_cmd;

	init_process(config);
	cmd_nmbr = ft_cmd_nmbr(config->cmd);
	if (open_files(config->cmd) == -1)
		return ;
	current_cmd = config->cmd;
	while (current_cmd && config->cmd_idx < cmd_nmbr)
	{
		spawn_child_process(config, current_cmd);
		current_cmd = current_cmd->next;
		config->cmd_idx++;
	}
	parent(config);
}

/*

first cmd take input from infile or stdin(0)
other cmds take input from infile or pipe[0]

last cmd return output to outfile or stdout(1)
other cmds return output to outfile or pipe[1]

the problem here is to close fds

close(infile) / close(pipe[0])
close(outfile) / close(pipe[1])

*/


// int main(int argc, char **argv, char **env)
// {
// 	t_parse	*cmd;

// }


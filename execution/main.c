


#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../mini/minishell/minishell.h"





void	run_child_process(t_process *process)
{
	int in;
	int out;

	in = redirection_in(process);
	out = redirection_out(process);
	close(process->pipe[0]);
	// if (process->cmd_idx == 0)
	// 	first_cmd(process, in);
	// if (!process->exec_cmd->next)
	// 	last_cmd(process, out);
	if (in != 0)
		if (dup2(in, 0) == -1)
			/*return error*/;
	ft_close_in(process);
	if (process->exec_cmd->next && out != 1)
		if (dup2(out, 1) == -1)
			/*return error*/;
	ft_close_out(process);
	execute_cmd(process);
}

void	spawn_child_process(t_process *process)
{
	pid_t pid;

	if (process->exec_cmd->next)
		if (pipe(process->pipe) == -1)
			/*return an error*/ ;
	pid = fork();
	if (pid == -1)
		/*return error*/ ;
	else if (pid == 0)
		run_child_process(process);
	close(process->saved_fd);
	process->saved_fd = dup(process->pipe[0]);
	if (process->saved_fd == -1)
		/*return error*/
	close(process->pipe[1]);
	close(process->pipe[0]);
}

void	init_process(t_process *process, t_parse *cmd)
{
	process->exec_cmd = cmd;
	process->env = cmd->env;
	process->path = NULL;
	process->cmd_idx = 0;
	process->saved_fd = -1;
}

void	execution(t_parse **cmd, t_process *process)
{
	pid_t	pid;
	int cmd_nmbr;

	init_process(process, *cmd);
	cmd_nmbr = ft_cmd_nmbr(process->exec_cmd); 
	while (process->exec_cmd && process->cmd_idx < cmd_nmbr)
	{
		spawn_child_process(process);
		process->exec_cmd = process->exec_cmd->next;
		process->cmd_idx++;
	}
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


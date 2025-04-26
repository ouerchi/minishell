#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../minishell/minishell.h"


void	*get_path(t_process *process)
{
	t_parse *exec_cmd = process->exec_cmd;

	if (exec_cmd->cmd_name[0] == '/' || (exec_cmd->cmd_name[0] == '.' && (exec_cmd->cmd_name[1] == '/' || exec_cmd->cmd_name[1] == '.')))
	{
		if (access(exec_cmd->cmd_name, F_OK) != 0)
			/*return error*/;
		if (access(exec_cmd->cmd_name, X_OK) != 0)
			/*return error*/;
		process->path = exec_cmd->cmd_name;
	}
	else
	{
		process->path = find_path(exec_cmd->cmd_name, process);
		if (!process->path)
			/*return error*/;
	}
}

char	*find_path(char *cmd_name, t_process *process)
{
	char **path_dirs;
	char *dir;
	char *cmd_dir;
	int i;

	path_dirs = ft_split(getenv("PATH"), ":");
	if (!path_dirs || !*path_dirs)
		/*return error*/;
	i = 0;
	while (path_dirs[i])
	{
		dir = ft_strjoin(path_dirs[i], "/");
		cmd_dir = ft_strjoin(dir, process->exec_cmd->cmd_name);
		free(dir);
		if (access(cmd_dir, F_OK | X_OK) == 0)
			return(free(path_dirs), cmd_dir);
		free(cmd_dir);
		i++;
	}
	return (free(path_dirs), NULL);
}

void	exec_cmd(t_process *process)
{
	get_path(process);
	execve(process->path, process->exec_cmd->args, process->env);
	/*return error*/;
}
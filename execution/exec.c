
#include "../minishell.h"

void	error_handling(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}

// void	free_array(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// }
char	*find_path(char *cmd_name, char **env)
{
	char **path_dirs;
	char *dir;
	char *cmd_dir;
	int i;

	path_dirs = ft_split(ft_getenv(env, "PATH"), ":");
	if (!path_dirs || !*path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		dir = ft_strjoin(path_dirs[i], "/");
		cmd_dir = ft_strjoin(dir, cmd_name);
		free(dir);
		if (access(cmd_dir, F_OK | X_OK) == 0)
			return(free(path_dirs), cmd_dir);
		free(cmd_dir);
		i++;
	}
	return (free_array(path_dirs), cmd_name);
}

void	get_path(t_config *config, t_parse *cmd)
{
	if (cmd->cmd_name[0] == '/' || (cmd->cmd_name[0] == '.' && (cmd->cmd_name[1] == '/' || cmd->cmd_name[1] == '.')))
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
	get_path(config, cmd);
	execve(config->path, cmd->args, config->env);
	error_handling(cmd->args[0], ": Command not found");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:20 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/07 14:14:17 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_token_list(t_token *lst)
{
    t_token *tmp;

    while (lst)
    {
        tmp = lst;
        lst = lst->next;
        free(tmp->value);
        free(tmp);
    }
}

void free_parse(t_parse *cmd)
{
    t_parse *tmp;
    int i;

    while (cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        free(tmp->cmd_name);
        if (tmp->args)
        {
            i = 0;
            while (tmp->args[i])
                free(tmp->args[i++]);
            free(tmp->args);
        }
        while (tmp->file)
        {
            free(tmp->file->name);
            free(tmp->file->type);
            free(tmp->file);
            tmp->file = tmp->file->next;
        }
        free(tmp);
    }
}

t_state_loop ft_state_loop(t_token *token, char *rl, t_config *config)
{
    // t_parse *cmd;
    t_error_type state;

    config->cmd = parse_piped_commands(&token);
    if (!config->cmd)
        return (CONTINUE);
    state = ft_handle_error(config->cmd, rl);
    if (state == ERR_UNCLOSED_QUOTES)
        return (free_parse(config->cmd), printf("minishell: Syntax error: Unclosed quotes\n"), CONTINUE);
    else
    {
        ft_print_list(config->cmd);
        execution(config);
        // free_parse(config->cmd);
        return (CONTINUE);
    }
}

void	minishell_loop(char **env)
{
	char        *rl;
    t_config    config;
	t_token     *token;
	t_state_loop state_loop;
    
    init_env(&config, env);
	while(1)
    {
        rl = readline("\x1b[32mminishell\x1b[34m-\x1b[31m$ \x1b[37m");
		if (!rl)
		{
			printf("\x1b[32mminishell\x1b[34m-\x1b[31m$ \x1b[37mexit\n");
		    break;
		}
		add_history(rl);
		token = ft_add_cmd(rl);
		if (validate_pipes(token))
		{
            if (ft_state_loop(token, rl, &config) == BREAK)
                break;
		}
		ft_free_token_list(token);
		free(rl);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argv;
	sig_int_handler();
	sig_ign_handler();
	if (argc == 1)
		minishell_loop(env);
    return (0);
}

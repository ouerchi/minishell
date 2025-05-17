/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:20 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 18:29:04 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state_loop	ft_state_loop(t_token *token, t_config *config)
{
	config->cmd = parse_piped_commands(&token, config);
	if (!config->cmd)
		return (CONTINUE);
	else
	{
		// ft_print_list(config->cmd);
		execution(config);
		return (CONTINUE);
	}
}

int	ft_break(t_token *token, t_config *config)
{
	int	val;

	val = validate_pipes(token, config);
	if (val == 1 || val == -1)
	{
		if (ft_ambi(token, config, 0, 0) == 1)
			return (1);
		if (ft_state_loop(token, config) == BREAK)
			return (0);
		if (val == -1)
			return (0);
	}
	return (1);
}

int	ft_continue(char *rl)
{
	t_error_type	state;

	state = ft_handle_error(rl);
	if (state == ERR_UNCLOSED_QUOTES)
	{
		printf("minishell: Syntax error: Unclosed quotes\n");
		return (0);
	}
	return (1);
}

void	minishell_loop(char **env)
{
	char		*rl;
	t_config	config;
	t_token		*token;

	init_env(&config, env);
	while (1)
	{
		rl = readline("minishell-$ ✗ ");
		if (!rl)
		{
			printf("minishell-$ exit\n");
			break ;
		}
		add_history(rl);
		if (ft_continue(rl) == 0)
			continue ;
		token = ft_add_cmd(rl, &config);
		// ft_print_list_2(token);
		if (ft_break(token, &config) == 0)
			break ;
		ft_free_token_list(token);
		free(rl);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc == 1)
		minishell_loop(env);
	return (0);
}

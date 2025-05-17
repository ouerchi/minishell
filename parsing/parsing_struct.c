/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:12:15 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 15:34:12 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_add_cmd(char *rl, t_config *config)
{
	int		i;
	t_token	*lst;

	i = 0;
	lst = NULL;
	while (rl[i])
	{
		while (rl[i] == ' ' || rl[i] == '\t')
			i++;
		if (!rl[i])
			break ;
		process_char(rl, &i, &lst, config);
	}
	return (lst);
}

t_parse	*ft_parsing(t_token **token, t_config *config)
{
	int		i;
	char	**arg;
	t_parse	*parse;

	parse = ft_parse_new();
	if (!parse)
		return (NULL);
	config->cmd = parse;
	arg = ft_check_parse(token, &config, &i);
	if (!arg)
	{
		free(parse);
		return (NULL);
	}
	parse->args = arg;
	if (i > 0)
		parse->cmd_name = ft_strdup(arg[0]);
	else
		parse->cmd_name = NULL;
	ft_builtins_check(parse);
	return (parse);
}

char	**ft_check_parse(t_token **check, t_config **config, int *i)
{
	int		size;
	char	**arg;

	size = count_words_before_pipe(*check) + 1;
	arg = (char **)malloc(sizeof(char *) * size);
	if (!arg)
		return (NULL);
	*i = 0;
	while ((*check) && ((*check)->type != T_PIPE))
	{
		if ((*check)->type == T_REDIR_IN || (*check)->type == T_REDIR_OUT
			|| (*check)->type == T_APPEND || (*check)->type == T_HERDOC)
			handle_redirection(check, &(*config)->cmd, (*config));
		else if ((*check)->type == T_WORD)
		{
			arg[(*i)++] = ft_strdup((*check)->value);
			(*check) = (*check)->next;
		}
		else
			(*check) = (*check)->next;
	}
	arg[*i] = NULL;
	return (arg);
}

t_parse	*parse_piped_commands(t_token **token_p, t_config *config)
{
	t_parse	*cmd;
	t_token	*token;

	cmd = ft_parsing(token_p, config);
	if (!cmd)
		return (NULL);
	token = *token_p;
	if (token && token->type == T_PIPE)
	{
		*token_p = token->next;
		cmd->next = parse_piped_commands(token_p, config);
		if (!cmd->next && *token_p)
			return (NULL);
	}
	return (cmd);
}

int	ft_ambi(t_token *token, t_config *config, int count, int count_2)
{
	t_token	*tok;

	while (token && token->next)
	{
		if (token->next
			&& (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
				|| token->type == T_APPEND)
			&& token->next->type == T_WORD
			&& (config->amb > 1 || config->flag_2 == 1))
		{
			tok = token->next;
			count = 1;
		}
		while (token && token->next && token->type != T_PIPE)
			token = token->next;
		print_amb(tok, &count, &count_2);
		token = token->next;
	}
	config->flag_2 = 0;
	config->amb = 0;
	return (count_2);
}

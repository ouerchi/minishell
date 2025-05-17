/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:47:03 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/17 18:50:05 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_expanding_her(char *rl_her, t_config *config, int *flag)
{
	int			j;
	t_exp		exp;

	j = 0;
	exp.res = NULL;
	while (rl_her[j])
	{
		if (rl_her[j] == '$' && is_numeric_char(rl_her, j + 1) && (*flag) == 0)
			j += 1;
		else if (rl_her[j] == '$' && ((*flag) == 0))
		{
			exp.temp_var = ft_handle_name_her(rl_her, &j);
			exp.temp_val = ft_search_lst(config, exp.temp_var);
			exp.res = ft_strjoin_free(exp.res, exp.temp_val);
			free(exp.temp_var);
		}
		else
			exp.res = ft_strjoin_char(exp.res, rl_her[j]);
		j++;
	}
	exp.res = ft_strjoin_char(exp.res, '\n');
	return (exp.res);
}

static char	*ft_handle_words_her(char *rl)
{
	int		i;
	t_dec	dec;

	i = 0;
	dec.quote = 0;
	dec.buff = NULL;
	while (rl[i])
	{
		if (!handle_char(&dec, rl, &i))
			break ;
	}
	return (dec.buff);
}

int	ft_if(t_token *token)
{
	t_token	*next_token;

	next_token = token->next;
	if (!next_token || next_token->type == T_PIPE
		|| next_token->type == T_REDIR_IN || next_token->type == T_REDIR_OUT
		|| next_token->type == T_APPEND || next_token->type == T_HERDOC)
		return (0);
	return (1);
}

int	extra_her(t_token *token, t_her *her)
{
	her->val = validate_pipes_her(token, her);
	if (her->val == 1 && ft_find_her(token) > 16)
		return (printf("minishell: maximum here-document count exceeded\n"), 0);
	else if (her->val == 0 && her->count_per > 16)
		return (printf("minishell: maximum here-document count exceeded\n"), 0);
	return (1);
}

int	hna_her(t_config *config, t_token *token, int *flag)
{
	t_her	her;

	her.flag = 0;
	her.count_per = 0;
	if (extra_her(token, &her) == 0)
		return (0);
	her.fd = open("her", O_CREAT | O_APPEND | O_RDWR, 777);
	her.fd_beg = open("her", O_CREAT | O_APPEND | O_RDWR, 777);
	// unlink("her");
	(*flag) = 1;
	while (token)
	{
		if (token->next && token->type == T_HERDOC && token->next->type == T_WORD)
		{
			her.rl_her = readline("> ");
			while (her.rl_her)
			{
				if (has_q(token->next->exp) == 0)
					her.flag = 1;
				her.temp = ft_handle_words_her(token->next->exp);
				if (ft_strcmp_her(her.rl_her, her.temp) == INT_MIN || !ft_strcmp_her(her.rl_her, her.temp))
					break ;
				her.check = ft_expanding_her(her.rl_her, config, &her.flag);
				write(her.fd, her.check, ft_strlen(her.check));
				her.rl_her = readline("> ");
			}
			her.flag = 0;
		}
		token = token->next;
	}
	return (1);
}

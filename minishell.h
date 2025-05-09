/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:26 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/09 21:59:19 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/wait.h>
# define _POSIX_C_SOURCE 200809L
# define _XOPEN_SOURCE 700
# define CD_HOME 0

typedef struct s_dec
{
	char	*buff;
	char	*temp;
	char	quote;
}	t_dec;

typedef struct s_exp
{
	int			count;
	char		*res;
	char		*temp;
	char		*temp_var;
	char		*temp_val;
}	t_exp;

typedef enum e_token
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HERDOC,
	T_SIGN,
	T_SQUOTE,
	T_DQUOTE,
}	t_token_type;

typedef enum e_quotes
{
	NONE,
	S_QUOTES,
	D_QUOTES,
}	t_quotes_state;

typedef enum e_loop
{
	BREAK,
	CONTINUE,
}	t_state_loop;

typedef enum e_error
{
	ERR_NONE,
	ERR_SYNTAX,
	ERR_NO_FILE,
	ERR_NUM_ARG,
	ERR_TOO_MANY_ARGS,
	ERR_INVALID_OPTION,
	ERR_UNCLOSED_QUOTES,
	ERR_PERMISSION_DENIED,
}	t_error_type;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_quotes
{
	int	single_q;
	int	double_q;
}	t_quotes;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_files
{
	char			*name;
	char			*type;
	struct s_files	*next;
}	t_files;

typedef struct s_parse
{
	char			*cmd_name;
	char			**args;
	t_files			*file;
	int				builtins;
	int				infile;
	int				outfile;
	struct s_parse	*next;
}	t_parse;

typedef struct s_env
{
	char			*variable;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_process
{
	int		saved_fd;
	int		pipe[2];
	int		cmd_idx;
	char	*path;
}	t_process;

typedef struct s_config
{
	t_parse	*cmd;
	t_env	*env_lst;
	char	**env;
	bool	fail;
	bool	env_exist;
	int		saved_fd;
	int		pipe[2];
	int		cmd_idx;
	char	*path;
}	t_config;

int				is_numeric(char *str);
char			*ft_handle_words(char *rl, int i);
void			ft_handle_redir_out(char *rl, int *i, t_token **lst);
void			ft_handle_redir_in(char *rl, int *i, t_token **lst);
void			ft_handle_word(char *rl, int *i, t_token **lst);
char			*ft_strjoin(char *s1, char *s2);
void			free_parse(t_parse *cmd);
void			ft_free_token_list(t_token *lst);
int				count_words_before_pipe(t_token *token);
char			*ft_strjoin_char(char *s1, char c);
void			ft_lstadd_back_files(t_parse **lst, t_files *new);
t_files			*ft_files_new(char *name, char *type);
int				ft_strcmp(char *str1, char *str2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
t_token			*ft_token_new(t_token_type type, void *content);
void			ft_lstadd_back_token(t_token **lst, t_token *new);
t_token			*ft_lstlast_token(t_token *lst);
void			sig_ign_handler(void);
void			sig_int_handler(void);
t_parse			*ft_parsing(t_token **token, t_config *config);
t_parse			*ft_parse_new(void);
char			*ft_strdup(char *s);
t_token			*ft_add_cmd(char *rl);
t_parse			*parse_piped_commands(t_token **token_p, t_config *config);
char			**ft_check_parse(t_token **check, t_config **config, int *i);
int				ft_lstsize_token(t_token *token);
void			ft_builtins_check(t_parse *par);
int				f_strcmp(const char *s1, const char *s2);
t_quotes_state	ft_handle_quotes(char *rl);
t_error_type	ft_handle_error(char *rl);
void			ft_print_list(t_parse *cmd);
size_t			ft_strlen(char *str);
char			*ft_strtrim(char *s1, char *set);
void			ft_print_list_2(t_token *cmd);
int				validate_pipes(t_token *token);
char			*ft_strchr(char *s, int c);
char			*ft_strcpy(char *dest, char *src);
char			*ft_substr(char *s, unsigned int start, size_t len);
void			handle_redirection(t_token **check, t_parse **p);
void			process_char(char *rl, int *i, t_token **lst);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_expanding(t_token *check, t_config *config);
char			*ft_handle_buff(char *rl, int *i);
void			init_env(t_config *config, char **env);
char			*trim_free(char *str);
char			*ft_getenv(char **env, char *env_name);
char			**get_env(char **real_env);
int				fail_check(char ***env, int i);
t_env			*get_env_lst(t_config *config);
void			append_env_lst(t_env **lst, char *variable);
void			free_lst(t_env **lst);
void			free_env_lst(t_env *env);
char			**ft_split_var(char *variable);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);
char			*ft_search_lst(t_config *config, char *buff);
char			*skip_char(char *str, char set);
char			*ft_handle_no_in_q(t_config *config, t_token *check, int j);
int				is_numeric_char(char *str, int i);
int				is_alpha_char(char *str, int i);
int				ft_isalnum(int ch);
int				ft_isdigit(int ch);
int				ft_isalpha(int ch);
char			*ft_strjoin_free(char *s1, char *s2);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_exp_par(char *buff, t_config *config, t_token *check);
char			*ft_handle_num_dol(char *buff, int *i);
char			*ft_handle_name(char *buff, int *i);
char			*ft_handle_num_dol(char *buff, int *i);
int				ft_calc_dol(char *buff, int i);
void			ft_quotes_exp(char *buff, int *i, t_quotes *quotes);
char			*merge_temp(char *buff, int *i, char *temp, t_quotes *quotes);
char			**ft_split(char *s, char *delims);
size_t			ft_strlcpy(char *dst, char *src, size_t dstsize);

int				execution(t_config *config);
void			execute_cmd(t_config *config, t_parse *cmd);
int	spawn_child_process(t_config *config, t_parse *cmd);
int	run_builtins(t_config *config);
void			check_env(t_config *config);
void			update_env(t_config *config);
void			free_array(char **arr);
char			**lst_to_array(t_env *env_lst);
int 			ft_cd(char *path, char **env);
int				ft_exit(char **arg);
int				ft_unset(t_config *config, char **args);
int				ft_pwd(t_config *config);
int				ft_env(t_env *env_lst);
int				ft_echo(char *str);

#endif
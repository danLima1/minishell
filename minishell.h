/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:18:07 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/27 10:29:29 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_printf/ft_printf.h"
# include "Libft/libft.h"

# define MAX_PATH 4096
# define MAX_ARGS 1024

extern int	g_signal_received;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_QUOTED,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}	t_token;

typedef struct s_redir
{
	t_token_type		type;
	char				*file;
	char				*eof;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char				**args;
	t_redir				*redirs;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_shell
{
	t_env				*env;
	int					exit_status;
	int					stdin_backup;
	int					stdout_backup;
	int					should_exit;
}	t_shell;

/* Legacy precisa de refatoracao */
char		**ms_split(const char *s);
int			count_words(const char *s);
t_token		*newnode(char *v, t_token_type type);
t_token		*node_last(t_token *node);
void		nodeadd_back(t_token **lst, t_token *new);
void		skip_words(const char *s, int *i);
void		handle_redd(const char *s, int *i);
int			handle_q(const char *s, int *i);
void		free_nodelist(t_token *list);
void		split_process(char *input);

/* Lexer  */
t_token		*lexer_tokenize(char *input);
void		print_tokens(t_token *tokens);
int			validate_tokens(t_token *tokens);
void		add_quoted_token(char *token, t_token **ls);
void		add_pipe_token(char *token, t_token **ls);

/* Parser  */
t_cmd		*parse_tokens(t_token *tokens, t_shell *shell);
void		free_cmd_list(t_cmd *cmd_list);
void		print_cmd_list(t_cmd *cmd_list);
int			count_commands(t_cmd *cmd);
t_cmd		*create_cmd(void);
t_token		*handle_redd_arg(t_cmd *current_cmd, t_token *t);

/* Expander  */
char		*expand_string(char *str, t_shell *shell);

/* Executor  */
int			execute_command(t_cmd *cmd, t_shell *shell);
int			is_builtin(char *cmd);
int			execute_builtin(char **args, t_shell *shell);
int			execute_single_command(t_cmd *cmd, t_shell *shell);
int			execute_pipeline(t_cmd *cmd_list, t_shell *shell);
char		*find_executable(char *cmd, t_env *env);
char		*get_path_env(t_env *env);
int			handle_redirections(t_redir *redirs);
int			handle_heredoc(char *delimiter);
void		setup_child_pipes(int prev_fd, int *pipe_fd, t_cmd *current);
void		execute_child_process(t_cmd *current, t_shell *shell);

/* Builtins  */
int			builtin_echo(char **args);
int			builtin_pwd(char **args);
int			builtin_env(char **args, t_env *env);
int			builtin_exit(char **args, t_shell *shell);
int			builtin_cd(char **args, t_env *env);
int			builtin_export(char **args, t_env **env);
int			builtin_unset(char **args, t_env **env);

/* Env  */
t_env		*init_env(char **envp);
t_env		*create_env_node(char *key, char *value);
void		add_env_node(t_env **env, t_env *new_node);
void		free_env(t_env *env);
char		**env_to_array(t_env *env);
void		free_env_array(char **envp);

/* Utils  */
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*ft_strcpy(char *dest, const char *src);

/* Error */
void		error_print(char *cmd, char *arg, char *msg);
void		error_exit(char *msg, int exit_code);

/* Signal */
void		signals_init(void);
void		signals_handle_sigint(int sig);
void		signals_handle_sigquit(int sig);


#endif

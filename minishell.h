/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:18:07 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/06 21:41:40 by ldos_sa2         ###   ########.fr       */
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
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
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
}	t_shell;

/* Legacy functions (to be refactored) */
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

/* Lexer functions */
t_token		*lexer_tokenize(char *input);
void		lexer_free_tokens(t_token *tokens);

/* Parser functions */
t_cmd		*parser_parse(t_token *tokens);
void		parser_free_cmds(t_cmd *cmds);

/* Expander functions */
char		*expander_expand(char *str, t_shell *shell);
char		*expander_get_var(char *var, t_shell *shell);

/* Executor functions */
int			executor_execute(t_cmd *cmds, t_shell *shell);
int			executor_exec_cmd(t_cmd *cmd, t_shell *shell);

/* Builtins functions */
int			builtin_echo(char **args);
int			builtin_cd(char **args, t_shell *shell);
int			builtin_pwd(void);
int			builtin_export(char **args, t_shell *shell);
int			builtin_unset(char **args, t_shell *shell);
int			builtin_env(t_shell *shell);
int			builtin_exit(char **args, t_shell *shell);
int			is_builtin(char *cmd);

/* Environment functions */
t_env		*env_init(char **envp);
char		*env_get(char *key, t_env *env);
void		env_set(char *key, char *value, t_env **env);
void		env_unset(char *key, t_env **env);
char		**env_to_array(t_env *env);
void		env_free(t_env *env);

/* Utils functions */
char		*utils_strjoin_free(char *s1, char *s2);
char		**utils_split_path(char *path);
char		*utils_find_executable(char *cmd, t_env *env);
void		utils_free_array(char **array);

/* Error functions */
void		error_print(char *cmd, char *arg, char *msg);
void		error_exit(char *msg, int exit_code);

/* Signal functions */
void		signals_init(void);
void		signals_handle_sigint(int sig);
void		signals_handle_sigquit(int sig);

#endif
